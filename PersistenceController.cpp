#include "PersistenceController.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QCoreApplication>
#include <QDebug>
#include <libusb.h>
#include <vector>
#include <QLoggingCategory>

// Defina a categoria de log para o controlador de persistência
Q_DECLARE_LOGGING_CATEGORY(usb)
Q_LOGGING_CATEGORY(usb, "usb.persistence")

PersistenceController* PersistenceController::instance = nullptr;

PersistenceController::PersistenceController(QObject *parent) : QObject(parent), usbDevice(nullptr), mcuFwUpModel(new MCUFirmwareUpload) {
    libusb_init(&usbContext); // Inicializa o contexto USB

    boardList.append(Ecu1Board::getInstance());
    boardList.append(Ecu2Board::getInstance());
    boardList.append(Ecu3Board::getInstance());
    boardList.append(Ecu4Board::getInstance());
    boardList.append(Mcu1Board::getInstance());

    qDebug() << "PersistenceController inicializado. Tamanho de boardList:" << boardList.size();
    for (Board* boardInfo : boardList) {
        if (boardInfo) {
            qDebug() << "Board adicionado. boardId:" << boardInfo->getBoardIdentification() << "commPortId:" << boardInfo->getSerialCommPort().getCommPortId();
        } else {
            qDebug() << "Erro: Ponteiro nulo adicionado em boardList.";
        }
    }

    if (boardList.isEmpty()) {
        qDebug() << "Erro: boardList está vazia.";
    } else {
        qDebug() << "Não ta vázio";
    }

    qDebug() << "Inicializando serialComm no construtor ";
    clearSerialComm();

    mcuFwUpModel = MCUFirmwareUpload::getInstance();
    ecuFwUpModel = ECUFirmwareUpload::getInstance();
    usbDevice = nullptr;
}

PersistenceController::~PersistenceController() {

    qDebug() << "Destruição do PersistenceController iniciada...";

    if (usbContext != nullptr) {
        libusb_exit(usbContext); // Libera o contexto USB
    }

    // Limpar a memória alocada para QSerialPort
    clearSerialComm();
}

PersistenceController* PersistenceController::getInstance() {
    if (!instance) {
        instance = new PersistenceController(qApp);
    }
    return instance;
}

libusb_device* PersistenceController::findUsbDevice(libusb_device **devs, uint16_t vid, uint16_t pid) {
    libusb_device *found = nullptr;
    libusb_device *device;
    libusb_device_descriptor desc;

    for (size_t i = 0; (device = devs[i]) != nullptr; ++i) {
        int r = libusb_get_device_descriptor(device, &desc);
        if (r < 0) {
            qWarning() << "Failed to get device descriptor";
            continue;
        }
        if (desc.idVendor == vid && desc.idProduct == pid) {
            found = device;
            break;
        }
    }
    return found;
}

QSerialPort* PersistenceController::getSerialCommPort(int index) {
    if (index >= 0 && index < serialComm.size()) {
        return serialComm[index];
    }
    return nullptr;
}

void PersistenceController::clearSerialComm() {
    qDebug() << "Limpando serialComm, tamanho atual: " << serialComm.size();
    for (QSerialPort* port : serialComm) {
        qDebug() << "Deletando porta serial: " << port->portName();
        delete port;
    }
    serialComm.clear();
    qDebug() << "serialComm limpo, tamanho atual: " << serialComm.size();
}

//Está em desuso
void PersistenceController::addSerialCommPort(QSerialPort* port) {
    serialComm.push_back(port);
}

int PersistenceController::getSerialCommSize() const {
    return serialComm.size();
}

int PersistenceController::loadSerialCommPorts() {
    int numberOfPorts;
    int ecuBoardFound = 0;
    int mcuBoardFound = 0;
    QList<SerialCommPort> ecuPortList;

    qDebug() << "Passou do 1° passo na loadSerialCommPorts";
    auto ports = QSerialPortInfo::availablePorts();  // Obtém as portas seriais disponíveis
    numberOfPorts = ports.size();  // Obtém o número de portas

    qDebug() << "Numero de portas: " << numberOfPorts;
    qDebug() << "Passou do 2° passo na loadSerialCommPorts";

    // Verifica se há portas disponíveis
    if (numberOfPorts <= 0) {
        return numberOfPorts;
    }

    qDebug() << "Inicializando serialComm";
    qDebug() << "Tamanho atual: " << serialComm.size();
    clearSerialComm();  // Limpa a lista de comunicação serial


    int ecu_vid = SystemProperties::getProperty(SystemProperties::ECU_VID).toInt();  // Obtém o VID da ECU
    int mcu_vid = SystemProperties::getProperty(SystemProperties::MCU_APP_VID).toInt();  // Obtém o VID da MCU

    qDebug() << "Resetando informações das boards";
    for (Board* boardInfo : boardList) {
        if (boardInfo != nullptr) {
            boardInfo->resetBoardData();  // Reseta os dados das placas
        } else {
            qDebug() << "Ponteiro de Board nulo";
        }
    }

    qDebug() << "Checando portas de comunicação ECU e MCU";
    for (int i = 0; i < numberOfPorts; ++i) {
        qDebug() << "Checando porta" << i;
        QSerialPort* serialPort = new QSerialPort(ports[i]);
        serialComm.append(serialPort);  // Adiciona a porta à lista serialComm

        if (ecu_vid == ports[i].vendorIdentifier()) {
            qDebug() << "ECU VID encontrado para porta" << i;
            SerialCommPort serialCommPort(ports[i], i);
            ecuPortList.append(serialCommPort); // Adiciona a porta à lista de ECUs
            ecuBoardFound++;
        } else if (mcu_vid == ports[i].vendorIdentifier()) {
            qDebug() << "MCU VID encontrado para porta" << i;
            setBoardInformation(i, JigaTestInterface::MCU1_BOARD_ID);  // Configura a informação da placa MCU
            mcuBoardFound++;
        }
    }
    qDebug() << "serialComm inicializado com" << getSerialCommSize() << "portas";

    qDebug() << "Obtendo todos os últimos índices de ECU";
    QVector<int> ecuPortLastIndex(ecuBoardFound);

    qDebug() << "Populando o array de índices";
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

    qDebug() << "Adicionando boards";

    int boardId = 0;
    for (int i = 0; i < ecuBoardFound; ++i) {

            if (i < ecuPortLastIndex.size()) {
                for (int j = 0; j < ecuPortList.size(); ++j) {
                    qDebug() << "Tentando configurar boardId" << boardId << "com portId" << ecuPortList[j].getCommPortId() << "onde ecuPortLastIndex[i] ==" << ecuPortLastIndex[i];
                    if (ecuPortLastIndex[i] == boardId) {
                        setBoardInformation(ecuPortList[boardId].getCommPortId(), boardId);  // Configura a informação da placa
                        boardId++;  // Incrementa o boardId após configurar
                        break; // Encontramos a correspondência, saímos do loop interno
                    }
                }
            } else {
                qDebug() << "Índice" << i << "fora do limite de ecuPortLastIndex";
                    return -1;  // Retorna erro
            }
    }
//    for (int i = 0; i < ecuBoardFound; ++i) {

//            if (i < ecuPortLastIndex.size()) {
//                for (int j = 0; j < ecuPortList.size(); ++j) {
//                    if (ecuPortLastIndex[i] == ecuPortList[j].getPortLocationIndex()) {
//                        setBoardInformation(ecuPortList[j].getCommPortId(), boardId);  // Configura a informação da placa
//                        boardId++;  // Incrementa o boardId após configurar
//                        break; // Encontramos a correspondência, saímos do loop interno
//                    }
//                }
//            } else {
//                qDebug() << "Índice" << i << "fora do limite de ecuPortLastIndex";
//                    return -1;  // Retorna erro
//            }
//    }


    qDebug() << "Concluído com" << (ecuBoardFound + mcuBoardFound) << "boards encontradas";
    return (ecuBoardFound + mcuBoardFound);  // Retorna o número total de placas encontradas
}

QVector<SerialCommPort*> PersistenceController::findSerialCommPorts() {
    auto ports = QSerialPortInfo::availablePorts();
    QVector<SerialCommPort*> serialCommPortList;
    for (int i = 0; i < ports.size(); ++i) {
        serialCommPortList.push_back(new SerialCommPort(ports[i], i));
    }
    return serialCommPortList;
}

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

void PersistenceController::setCommPortFound(int index, int commPortId) {
    if (index >= 0 && index < foundCommPorts.size()) {
        foundCommPorts[index] = commPortId;
    } else if (index == foundCommPorts.size()) {
        foundCommPorts.append(commPortId);
    }
}

int PersistenceController::getCommPortFound(int index) const {
    if (index >= 0 && index < foundCommPorts.size()) {
        return foundCommPorts[index];
    }
    return -1;
}

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

bool PersistenceController::openConnection(int portId, int baudRate) {
    // Verifica se o portId é válido
    if (portId >= serialComm.size()) {
        return false;
    }

    qDebug() << "Essa é o port Id: " << portId;
    qDebug() << "Esse é o baud rate: " << baudRate;
    qDebug() << "Tamanho do serialComm: " << serialComm.size();

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

bool PersistenceController::openBoardConnection(int boardId, int baudrate) {
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            return openConnection(boardInfo->getSerialCommPort().getCommPortId(), baudrate);
        }
    }
    return false;
}

//bool PersistenceController::openBoardConnection(int boardId) {
//    qDebug() << "Board Id: " << boardId;

//    for (Board* boardInfo : boardList) {
//        if (boardInfo->getBoardIdentification() == boardId) {
//            qDebug() << "Abrindo porta com board id" << boardId;
//            return openConnection(boardInfo->getSerialCommPort().getCommPortId(), boardInfo->getBoardBaudRate());
//        }
//    }

//    return false;
//}

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

QString PersistenceController::getPortDescription(int index) {
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index is out of range in getPortDescription.";
        return QString();
    }

    QSerialPort* port = serialComm[index];
    QSerialPortInfo portInfo(*port);
    return portInfo.description();
}

QString PersistenceController::getDescriptivePortName(int index) {
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index is out of range in getDescriptivePortName.";
        return QString();
    }

    QSerialPort* port = serialComm[index];
    QSerialPortInfo portInfo(*port);
    return portInfo.portName();
}

QString PersistenceController::getBoardCommPort(int boardId) {
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            return boardInfo->getSerialCommPort().getSystemPortName();
        }
    }
    return QString();
}

QString PersistenceController::getBoardDescription(int boardId) {
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            return boardInfo->getBoardDescription();
        }
    }
    return QString();
}

int PersistenceController::getTotalNumberOfPorts() {
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    return availablePorts.size();
}

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

void PersistenceController::setBoardInformation(int portId, int boardId) {

    if (portId < 0 || portId >= serialComm.size()) {
        qDebug() << "Índice da porta está fora do intervalo.";
        return;
    }

    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            // Obter QSerialPortInfo a partir do QSerialPort
            QSerialPortInfo portInfo = QSerialPortInfo(*serialComm[portId]);

            boardInfo->getSerialCommPort().setSerialCommPort(portInfo, portId);
            qDebug() << "Set board information for board id" << boardId << "with port id" << portId;
        }
    }
}

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

void PersistenceController::setReportProperty(const QString &key, const QString &value) {
    reportProperties[key] = value;
}

QString PersistenceController::getReportProperty(const QString &key) const {
    return reportProperties.value(key);
}
