#include "PersistenceController.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QCoreApplication>
#include <QDebug>
#include <libusb.h>
#include <vector>
#include <QLoggingCategory>

// Define a categoria de log para o controlador de persistência
Q_DECLARE_LOGGING_CATEGORY(usb)
Q_LOGGING_CATEGORY(usb, "usb.persistence")

// Inicializa a instância singleton do PersistenceController como nullptr
PersistenceController* PersistenceController::instance = nullptr;

// Construtor da classe PersistenceController
PersistenceController::PersistenceController(QObject *parent)
    : QObject(parent), usbDevice(nullptr), mcuFwUpModel(new MCUFirmwareUpload) {
    libusb_init(&usbContext); // Inicializa o contexto USB

    // Adiciona as instâncias das placas à lista boardList
    boardList.append(Ecu1Board::getInstance());
    boardList.append(Ecu2Board::getInstance());
    boardList.append(Ecu3Board::getInstance());
    boardList.append(Ecu4Board::getInstance());
    boardList.append(Mcu1Board::getInstance());

    qDebug() << "PersistenceController inicializado. Tamanho de boardList:" << boardList.size();
    for (Board* boardInfo : boardList) {
        if (boardInfo) {
            qDebug() << "Board adicionado. boardId:" << boardInfo->getBoardIdentification()
                     << "commPortId:" << boardInfo->getSerialCommPort().getCommPortId();
        } else {
            qDebug() << "Erro: Ponteiro nulo adicionado em boardList.";
        }
    }

    // Verifica se a lista de placas está vazia
    if (boardList.isEmpty()) {
        qDebug() << "Erro: boardList está vazia.";
    } else {
        qDebug() << "Não está vazia";
    }

    qDebug() << "Inicializando serialComm no construtor";
    clearSerialComm(); // Limpa a comunicação serial existente

    mcuFwUpModel = MCUFirmwareUpload::getInstance(); // Inicializa modelos de upload de firmware
    ecuFwUpModel = ECUFirmwareUpload::getInstance();
    usbDevice = nullptr; // Inicializa o dispositivo USB como nulo
}

// Destrutor da classe PersistenceController
PersistenceController::~PersistenceController() {
    qDebug() << "Destruição do PersistenceController iniciada...";

    // Libera o contexto USB se foi inicializado
    if (usbContext != nullptr) {
        libusb_exit(usbContext); // Libera o contexto USB
    }

    // Limpa a memória alocada para QSerialPort
    clearSerialComm();
}

// Método estático para obter a instância singleton do PersistenceController
PersistenceController* PersistenceController::getInstance() {
    if (!instance) {
        instance = new PersistenceController(qApp); // Inicializa a instância
    }
    return instance;
}

// Método para encontrar um dispositivo USB específico com base em VID e PID
libusb_device* PersistenceController::findUsbDevice(libusb_device **devs, uint16_t vid, uint16_t pid) {
    libusb_device *found = nullptr;
    libusb_device *device;
    libusb_device_descriptor desc;

    // Itera pelos dispositivos USB disponíveis
    for (size_t i = 0; (device = devs[i]) != nullptr; ++i) {
        int r = libusb_get_device_descriptor(device, &desc);
        if (r < 0) {
            qWarning() << "Failed to get device descriptor";
            continue;
        }
        // Verifica se o VID e PID correspondem ao dispositivo desejado
        if (desc.idVendor == vid && desc.idProduct == pid) {
            found = device;
            break;
        }
    }
    return found;
}

// Obtém a porta de comunicação serial no índice especificado
QSerialPort* PersistenceController::getSerialCommPort(int index) {
    if (index >= 0 && index < serialComm.size()) {
        return serialComm[index];
    }
    return nullptr;
}

// Limpa a lista de portas de comunicação serial
void PersistenceController::clearSerialComm() {
    qDebug() << "Limpando serialComm, tamanho atual: " << serialComm.size();
    for (QSerialPort* port : serialComm) {
        qDebug() << "Deletando porta serial: " << port->portName();
        delete port; // Libera a memória da porta serial
    }
    serialComm.clear(); // Limpa a lista
    qDebug() << "serialComm limpo, tamanho atual: " << serialComm.size();
}

// Adiciona uma porta de comunicação serial à lista (método obsoleto)
void PersistenceController::addSerialCommPort(QSerialPort* port) {
    serialComm.push_back(port);
}

// Obtém o número total de portas de comunicação serial na lista
int PersistenceController::getSerialCommSize() const {
    return serialComm.size();
}

// Carrega as portas seriais disponíveis e identifica placas ECU e MCU conectadas
int PersistenceController::loadSerialCommPorts() {
    int numberOfPorts;
    int ecuBoardFound = 0;
    int mcuBoardFound = 0;
    QList<SerialCommPort> ecuPortList;

    auto ports = QSerialPortInfo::availablePorts();  // Obtém as portas seriais disponíveis
    numberOfPorts = ports.size();  // Obtém o número de portas

    qDebug() << "Numero de portas: " << numberOfPorts;

    // Verifica se há portas disponíveis
    if (numberOfPorts <= 0) {
        return numberOfPorts;
    }

    clearSerialComm();  // Limpa a lista de comunicação serial

    int ecu_vid = SystemProperties::getProperty(SystemProperties::ECU_VID).toInt();  // Obtém o VID da ECU
    int mcu_vid = SystemProperties::getProperty(SystemProperties::MCU_APP_VID).toInt();  // Obtém o VID da MCU

    // Reseta os dados das placas
    for (Board* boardInfo : boardList) {
        if (boardInfo != nullptr) {
            boardInfo->resetBoardData();
        } else {
            qDebug() << "Ponteiro de Board nulo";
        }
    }

    // Itera sobre as portas disponíveis para encontrar ECUs e MCUs
    for (int i = 0; i < numberOfPorts; ++i) {
        QSerialPort* serialPort = new QSerialPort(ports[i]);
        serialComm.append(serialPort);  // Adiciona a porta à lista serialComm

        if (ecu_vid == ports[i].vendorIdentifier()) {
            SerialCommPort serialCommPort(ports[i], i);
            ecuPortList.append(serialCommPort); // Adiciona a porta à lista de ECUs
            ecuBoardFound++;
        } else if (mcu_vid == ports[i].vendorIdentifier()) {
            setBoardInformation(i, JigaTestInterface::MCU1_BOARD_ID);  // Configura a informação da placa MCU
            mcuBoardFound++;
        }
    }
    qDebug() << "serialComm inicializado com" << getSerialCommSize() << "portas";

    // Ordena e configura informações das ECUs encontradas
    QVector<int> ecuPortLastIndex(ecuBoardFound);
    for (int i = 0; i < ecuBoardFound; ++i) {
        if (i < ecuPortList.size()) {
            for (int j = 0; j < serialComm.size(); ++j) {
                if (serialComm[j]->portName() == ecuPortList[i].getDescriptivePortName()) {
                    ecuPortLastIndex[i] = j;
                    break;
                }
            }
        } else {
            qDebug() << "Índice" << i << "fora do limite de ecuPortList";
                return -1;  // Retorna erro
        }
    }
    std::sort(ecuPortLastIndex.begin(), ecuPortLastIndex.end());  // Ordena os índices

    // Configura informações das placas ECU encontradas
    int boardId = 0;
    for (int i = 0; i < ecuBoardFound; ++i) {
        if (i < ecuPortLastIndex.size()) {
            for (int j = 0; j < ecuPortList.size(); ++j) {
                if (ecuPortLastIndex[i] == boardId) {
                    setBoardInformation(ecuPortList[boardId].getCommPortId(), boardId);  // Configura a informação da placa
                    boardId++;  // Incrementa o boardId após configurar
                    break;
                }
            }
        } else {
            qDebug() << "Índice" << i << "fora do limite de ecuPortLastIndex";
                return -1;  // Retorna erro
        }
    }

    qDebug() << "Concluído com" << (ecuBoardFound + mcuBoardFound) << "boards encontradas";
        return (ecuBoardFound + mcuBoardFound);  // Retorna o número total de placas encontradas
}

// Encontra e retorna uma lista de portas seriais disponíveis
QVector<SerialCommPort*> PersistenceController::findSerialCommPorts() {
    auto ports = QSerialPortInfo::availablePorts();
    QVector<SerialCommPort*> serialCommPortList;
    for (int i = 0; i < ports.size(); ++i) {
        serialCommPortList.push_back(new SerialCommPort(ports[i], i));
    }
    return serialCommPortList;
}

// Obtém informações detalhadas das portas seriais disponíveis
QVector<SerialCommPort*> PersistenceController::getSerialCommPortInfo() {
    auto ports = QSerialPortInfo::availablePorts();
    QVector<SerialCommPort*> serialCommPortList;
    for (int i = 0; i < ports.size(); ++i) {
        SerialCommPort* port = new SerialCommPort();
        port->setCommPortId(i);
        port->setDescriptivePortName(ports[i].portName());
        port->setPortDescription(ports[i].description());
        port->setSystemPortName(ports[i].systemLocation());
        serialCommPortList.push_back(port);
    }
    return serialCommPortList;
}

// Define a porta de comunicação encontrada associada a um índice
void PersistenceController::setCommPortFound(int index, int commPortId) {
    if (index >= 0 && index < foundCommPorts.size()) {
        foundCommPorts[index] = commPortId;
    } else if (index == foundCommPorts.size()) {
        foundCommPorts.append(commPortId);
    }
}

// Obtém a porta de comunicação encontrada com base no índice
int PersistenceController::getCommPortFound(int index) const {
    if (index >= 0 && index < foundCommPorts.size()) {
        return foundCommPorts[index];
    }
    return -1;
}

// Carrega o programador USB para a placa
bool PersistenceController::loadUsbProgrammer() {
    libusb_device *device = nullptr;
    libusb_device **devs = nullptr;
    libusb_context *ctx = nullptr;
    int r;
    ssize_t cnt;

    uint16_t vid = UtilsConversion::hexToShort(QString::fromStdString(qgetenv("MCU_PROG_VID").toStdString()));
    uint16_t pid = UtilsConversion::hexToShort(QString::fromStdString(qgetenv("MCU_PROG_PID").toStdString()));

    try {
        r = libusb_init(&ctx);
        if (r < 0) {
            qCritical() << "Init Error:" << r;
            return false;
        }

        cnt = libusb_get_device_list(ctx, &devs);
        if (cnt < 0) {
            qCritical() << "Get Device List Error";
            libusb_exit(ctx);
            return false;
        }

        device = findUsbDevice(devs, vid, pid);
    } catch (const std::exception &ex) {
        qCritical() << "Exception occurred:" << ex.what();
    }

    if (device != nullptr) {
        usbDevice = device;
        libusb_free_device_list(devs, 1);
        libusb_exit(ctx);
        return true;
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return false;
}

// Abre uma conexão com uma porta serial específica
bool PersistenceController::openConnection(int portId, int baudRate) {
    // Verifica se o portId é válido
    if (portId >= serialComm.size()) {
        return false;
    }

    QSerialPort* port = serialComm[portId];
    if (!port) {
        qDebug() << "Ponteiro serialComm[portId] é nulo.";
            return false;
    }

    // Verifica se a porta já está aberta
    if (port->isOpen()) {
        return true;
    }

    auto ports = QSerialPortInfo::availablePorts();
    if (portId >= ports.size()) {
        qDebug() << "Nao foi aberta no portId >= ports.size()";
        return false;
    }

    const QSerialPortInfo& portInfo = ports[portId];

    // Configurações da porta serial
    port->setBaudRate(baudRate);
    port->setPortName(portInfo.portName());
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    // Tenta abrir a porta
    if (!port->open(QIODevice::ReadWrite)) {
        qDebug() << "Nao foi aberta no QIODevice::ReadWrite:" << port->errorString();
        return false;
    }

    qDebug() << "Porta aberta com sucesso:" << portInfo.portName();
    return true;
}

// Abre a conexão com uma placa específica, identificando-a pelo boardId
bool PersistenceController::openBoardConnection(int boardId, int baudrate) {
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            return openConnection(boardInfo->getSerialCommPort().getCommPortId(), baudrate);
        }
    }
    return false;
}

// Abre a conexão com uma placa específica
bool PersistenceController::openBoardConnection(int boardId) {
    qDebug() << "Board Id: " << boardId;

    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            int commPortId = boardInfo->getSerialCommPort().getCommPortId();
            int baudRate = boardInfo->getBoardBaudRate();
            qDebug() << "Abrindo porta com board id" << boardId << "e comm port id" << commPortId;

            if (commPortId < 0 || commPortId >= serialComm.size()) {
                qDebug() << "Erro: commPortId inválido:" << commPortId;
                    return false;
            }

            return openConnection(commPortId, baudRate);
        }
    }
    qDebug() << "Board id" << boardId << "não encontrado";
        return false;
}

// Obtém a descrição da porta do sistema com base no índice fornecido
QString PersistenceController::getSystemPortDescription(int index) {
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index out of range in getSystemPortDescription.";
        return QString();
    }

    QSerialPort* port = serialComm[index];
    if (!port) {
        qDebug() << "Serial port at index" << index << "is null.";
        return QString();
    }

    return port->portName();
}

// Obtém a descrição da porta com base no índice fornecido
QString PersistenceController::getPortDescription(int index) {
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index is out of range in getPortDescription.";
        return QString();
    }

    QSerialPort* port = serialComm[index];
    QSerialPortInfo portInfo(*port);
    return portInfo.description();
}

// Obtém o nome descritivo da porta com base no índice fornecido
QString PersistenceController::getDescriptivePortName(int index) {
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index is out of range in getDescriptivePortName.";
        return QString();
    }

    QSerialPort* port = serialComm[index];
    QSerialPortInfo portInfo(*port);
    return portInfo.portName();
}

// Obtém a porta de comunicação da placa com base no boardId
QString PersistenceController::getBoardCommPort(int boardId) {
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            return boardInfo->getSerialCommPort().getSystemPortName();
        }
    }
    return QString();
}

// Obtém a descrição da placa com base no boardId
QString PersistenceController::getBoardDescription(int boardId) {
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            return boardInfo->getBoardDescription();
        }
    }
    return QString();
}

// Obtém o número total de portas disponíveis
int PersistenceController::getTotalNumberOfPorts() {
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    return availablePorts.size();
}

// Escreve dados na porta serial
void PersistenceController::serialWrite(int portId, const QString& atCmd, bool endOfLine) {
    if (portId >= serialComm.size()) {
        return;
    }
    QSerialPort* port = serialComm[portId];
    if (port->isOpen()) {
        QTextStream stream(port);
        if (endOfLine) {
            stream << atCmd << Qt::endl;
        } else {
            stream << atCmd;
        }
        stream.flush();
    }
}

// Escreve um comando na placa especificada pelo boardId
void PersistenceController::serialBoardWrite(int boardId, const QString &atCmd, bool endOfLine) {
    int commPortID = -1;

    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            commPortID = boardInfo->getSerialCommPort().getCommPortId();
            break;
        }
    }

    if (commPortID != -1) {
        serialWrite(commPortID, atCmd, endOfLine);
    } else {
        qDebug() << "Board ID not found or no communication port ID associated with this board.";
    }
}

// Fecha a conexão com a porta serial especificada
void PersistenceController::closeConnection(int portId) {
    if (portId < 0 || portId >= serialComm.size()) {
        qDebug() << "Port ID is out of range.";
        return;
    }

    QSerialPort* port = serialComm[portId];
    if (port && port->isOpen()) {
        port->close();
        qDebug() << "Port" << port->portName() << "closed successfully.";
    } else {
        qDebug() << "Port is not open or does not exist.";
    }
}

// Fecha a conexão com a placa especificada pelo boardId
void PersistenceController::closeBoardConnection(int boardId) {
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            closeConnection(boardInfo->getSerialCommPort().getCommPortId());
            qDebug() << "Connection closed for board ID" << boardId;
            return;
        }
    }
    qDebug() << "Board ID" << boardId << "not found.";
}

// Lê dados da porta serial
QString PersistenceController::serialRead(int portId) {
    static QRegularExpression newLineRegex("[\\r\\n]");

    if (portId < 0 || portId >= serialComm.size()) {
        qDebug() << "ID da porta está fora do intervalo.";
            return QString();
    }

    QSerialPort* port = serialComm[portId];
    if (!port->isOpen()) {
        qDebug() << "Porta não está aberta.";
        return QString();
    }

    QByteArray newData;
    QString recvStr;

    if (port->waitForReadyRead(100)) {
        newData = port->readAll();
        recvStr = QString::fromUtf8(newData);
        recvStr.remove(newLineRegex);
    } else {
        qDebug() << "Timeout na leitura ou nenhum dado disponível.";
    }

    return recvStr;
}

// Lê dados da placa especificada pelo boardId
QString PersistenceController::serialBoardRead(int boardId) {
    int commPortID = -1;

    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            commPortID = boardInfo->getSerialCommPort().getCommPortId();
            break;
        }
    }

    if (commPortID != -1) {
        return serialRead(commPortID);
    } else {
        qDebug() << "Board ID" << boardId << "not found or no communication port ID associated with this board.";
        return QString();
    }
}

// Escreve o firmware na placa e retorna o código de saída do processo
int PersistenceController::writeFirmware(int testId, int boardId, const QString& cmdStr) {
    int exitCode = 1;
    QString line;
    QProcess process;

    QStringList args;
#ifdef Q_OS_WIN
    args << "/c" << cmdStr;
    process.start("cmd.exe", args);
#else
    args << "-c" << cmdStr;
    process.start("sh", args);
#endif

    if (!process.waitForStarted()) {
        qDebug() << "Falha ao iniciar o processo.";
        return exitCode;
    }

    qDebug() << "##########################################################################";
    addCmdTestMessage(testId, boardId, "Iniciando o Programa AVRDUDE...", true);

    if (!process.waitForFinished(-1)) {
        qDebug() << "Processo não finalizado corretamente.";
            return exitCode;
    }

    QString stdError = process.readAllStandardError();
    QStringList errorLines = stdError.split('\n');

    for (const QString& errorLine : errorLines) {
        if (!errorLine.isEmpty()) {
            QString cleanedLine = errorLine.trimmed();
            addCmdTestMessage(testId, boardId, cleanedLine, false);
        }
    }

    exitCode = process.exitCode();
    qDebug() << "##########################################################################";
    qDebug() << "Exited with error code :" << exitCode;
    addCmdTestMessage(testId, boardId, "Finalizando o Programa AVRDUDE...", true);

    if (exitCode == 0) {
        line = "Firmware atualizado com sucesso!";
    } else {
        line = "Erro na atualização de firmware!";
    }

    addCmdTestMessage(testId, boardId, line, true);
    qDebug() << line;

    return exitCode;
}

// Configura as informações da placa com base no portId e boardId fornecidos
void PersistenceController::setBoardInformation(int portId, int boardId) {
    if (portId < 0 || portId >= serialComm.size()) {
        qDebug() << "Índice da porta está fora do intervalo.";
        return;
    }

    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            QSerialPortInfo portInfo = QSerialPortInfo(*serialComm[portId]);
            boardInfo->getSerialCommPort().setSerialCommPort(portInfo, portId);
            qDebug() << "Set board information for board id" << boardId << "with port id" << portId;
        }
    }
}

// Adiciona uma mensagem de teste ao modelo de upload de firmware da MCU
void PersistenceController::addCmdTestMessage(int testId, int boardId, const QString& testMessage, bool header) {
    QString strMessage;

    switch (testId) {
    case JigaTestInterface::MCU_FIRMWARE_UPLOAD:
        if (header) {
            strMessage = QString(CmdMessageConstants::CMD_HDR_FIRM_UPLOAD) + " ";
        }
        strMessage += testMessage;
        mcuFwUpModel->addTestMessage(boardId, strMessage);
        break;

    default:
        qDebug() << "Test ID not recognized:" << testId;
        break;
    }
}

// Define uma propriedade de relatório no mapa reportProperties
void PersistenceController::setReportProperty(const QString &key, const QString &value) {
    reportProperties[key] = value;
}

// Obtém uma propriedade de relatório com base na chave fornecida
QString PersistenceController::getReportProperty(const QString &key) const {
    return reportProperties.value(key);
}
