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

PersistenceController::PersistenceController(QObject *parent) : QObject(parent),usbDevice(nullptr) {
    libusb_init(&usbContext); // Inicializa o contexto USB

    boardList.append(Ecu1Board::getInstance());
    boardList.append(Ecu2Board::getInstance());
    boardList.append(Ecu3Board::getInstance());
    boardList.append(Ecu4Board::getInstance());
    boardList.append(Mcu1Board::getInstance());

    //fwUpdateModel = FirmwareUpload.getInstance();
    usbDevice = nullptr;

}


PersistenceController::~PersistenceController() {
    libusb_exit(usbContext); // Libera o contexto USB
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


int PersistenceController::findSerialCommPorts() {
    int numberOfPorts;
    QString ecuPortDesc, ecuDescPortName;
    QString mcuPortDesc, mcuDescPortName;
    QString retPortDesc, retDescPortName;
    int portFounds = 0;

    // 1- Obter o número de portas
    numberOfPorts = getTotalNumberOfPorts();

    // 2- Verificar se pelo menos uma porta foi encontrada
    if (numberOfPorts <= 0) {
        return numberOfPorts;
    }

    // 3- Obter descrições das propriedades do sistema
    ecuPortDesc = SystemProperties::getProperty(SystemProperties::ECU_PORT_DESCRIPTION);
    ecuDescPortName = SystemProperties::getProperty(SystemProperties::ECU_DESC_PORT_NAME);
    mcuPortDesc = SystemProperties::getProperty(SystemProperties::MCU_PORT_DESCRIPTION);
    mcuDescPortName = SystemProperties::getProperty(SystemProperties::MCU_DESC_PORT_NAME);

    // 4- Verificar se a porta está disponível
    for (int i = 0; i < numberOfPorts; ++i) {
        retPortDesc = getPortDescription(i);
        if (retPortDesc.startsWith(ecuPortDesc) || retPortDesc.startsWith(mcuPortDesc)) {
            setCommPortFound(portFounds, i);
            ++portFounds;
            continue;
        }
        retDescPortName = getDescriptivePortName(i);
        if (retDescPortName.startsWith(ecuDescPortName)) {
            setCommPortFound(portFounds, i);
            ++portFounds;
        } else if (retDescPortName.startsWith(mcuDescPortName)) {
            setCommPortFound(portFounds, i);
            ++portFounds;
        }
    }

    return portFounds;
}

QVector<SerialCommPort*> PersistenceController::getSerialCommPortInfo() {
    QVector<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    QVector<SerialCommPort*> serialCommPorts;

    for (int i = 0; i < availablePorts.size(); ++i) {
        const QSerialPortInfo &info = availablePorts[i];
        SerialCommPort* port = new SerialCommPort(this);
        port->setCommPortId(i);  // Passa o índice como identificador
        port->setDescriptivePortName(info.description());
        port->setPortDescription(info.manufacturer());
        port->setSystemPortName(info.portName());
        serialCommPorts.append(port);
    }

    return serialCommPorts;
}

void PersistenceController::setCommPortFound(int index, int commPortId)
{
    // Certifique-se de que o índice é válido
    if (index >= 0 && index < foundCommPorts.size()) {
        foundCommPorts[index] = commPortId;
    } else if (index == foundCommPorts.size()) {
        // Se o índice é igual ao tamanho do vetor, adicione um novo elemento
        foundCommPorts.append(commPortId);
    }
}

int PersistenceController::getCommPortFound(int index) const
{
    if (index >= 0 && index < foundCommPorts.size()) {
        return foundCommPorts[index];
    }
    return -1;  // Retorne um valor inválido se o índice for fora do intervalo
}

bool PersistenceController::loadUsbProgrammer()
{
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
    // Verifica se o índice da porta é válido
    if (portId < 0 || portId >= serialComm.size()) {
        qDebug() << "Port ID is out of range.";
        return false;
    }

    QSerialPort* port = serialComm[portId];

    // Se a porta não estiver aberta, tenta abrir
    if (!port->isOpen()) {
        port->setPortName(port->portName()); // Garanta que o nome da porta está definido corretamente
        port->setBaudRate(baudRate);
        port->setDataBits(QSerialPort::Data8);
        port->setParity(QSerialPort::NoParity);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);

        if (!port->open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open port" << port->portName() << "with error:" << port->errorString();
            return false;
        }
    } else {
        // A porta já está aberta, apenas reconfigure se necessário
        port->setBaudRate(baudRate);
    }

    // A porta foi aberta com sucesso e configurada
    qDebug() << "Port" << port->portName() << "opened successfully with baud rate" << baudRate;
    return true;

}

bool PersistenceController::openBoardConnection(int boardId, int baudRate)
{
    for(Board* boardInfo: boardList){
        if(boardInfo->getBoardIdentification()==boardId){
            return openConnection(boardInfo->getCommPortIdentification(),baudRate);
        }
    }
    return false;
}

bool PersistenceController::openBoardConnection(int boardId)
{
    int baudrate;

    for(Board* boardInfo: boardList){
        if(boardInfo->getBoardIdentification()==boardId){
            baudrate = boardInfo->getBoardBaudRate();
            return openConnection(boardInfo->getCommPortIdentification(),baudrate);
        }
    }
    return false;
}

QString PersistenceController::getSystemPortDescription(int index)
{
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index out of range in getSystemPortDescription.";
        return QString();  // Retorna uma QString vazia se o índice não for válido
    }

    QSerialPort* port = serialComm[index];
    if (!port) {
        qDebug() << "Serial port at index" << index << "is null.";
        return QString();  // Retorna uma QString vazia se o objeto da porta serial for nulo
    }

    // Retorna o nome do sistema para a porta serial
    return port->portName();  // 'portName()' retorna o identificador da porta, similar ao 'systemLocation()' usado em QSerialPortInfo
}

QString PersistenceController::getPortDescription(int index) {
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index is out of range in getPortDescription.";
        return QString();  // Retorna uma QString vazia se o índice não for válido
    }

    QSerialPort* port = serialComm[index];
    QSerialPortInfo portInfo(*port);
    return portInfo.description();  // Retorna a descrição humana da porta
}

QString PersistenceController::getDescriptivePortName(int index) {
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Index is out of range in getDescriptivePortName.";
        return QString();  // Retorna uma QString vazia se o índice não for válido
    }

    QSerialPort* port = serialComm[index];
    QSerialPortInfo portInfo(*port);
    return portInfo.portName();  // Retorna o nome descritivo da porta, geralmente o mesmo que o nome do sistema
}

QString PersistenceController::getBoardCommPort(int boardId)
{
    for(Board* boardInfo : boardList){
        if(boardInfo->getBoardIdentification() == boardId){
            return boardInfo->getCommPortName();
        }
    }

    return QString();
}

QString PersistenceController::getBoardDescription(int boardId)
{
    for(Board* boardInfo : boardList){
        if(boardInfo->getBoardIdentification() == boardId){
            return boardInfo->getBoardDescription();
        }
    }
    return QString();
}

int PersistenceController::getTotalNumberOfPorts()
{
    // Usa QSerialPortInfo para obter uma lista de informações sobre portas seriais disponíveis
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    // Retorna o tamanho da lista, que representa o número de portas seriais disponíveis
    return availablePorts.size();
}

void PersistenceController::serialWrite(int portId, const QString& atCmd, bool endOfLine) {
    // Verifica se o índice da porta é válido
    if (portId < 0 || portId >= serialComm.size()) {
        qDebug() << "Port ID is out of range.";
        return;
    }

    QSerialPort* port = serialComm[portId];
    if (!port->isOpen()) {
        qDebug() << "Port is not open.";
        return;
    }

    QString command = atCmd;
    if (endOfLine) {
        command.append("\n");  // Adiciona uma nova linha se endOfLine for verdadeiro
    }

    // Envia o comando para a porta serial
    qint64 bytesWritten = port->write(command.toUtf8());

    if (bytesWritten == -1) {
        qDebug() << "Failed to write to the serial port:" << port->errorString();
    } else if (bytesWritten < command.size()) {
        qDebug() << "Not all data was written to the serial port.";
    } else {
        port->flush();  // Garante que todos os dados sejam enviados
    }

    // Espera um pequeno delay para garantir que os dados tenham tempo de ser enviados
    QThread::msleep(50);
}

void PersistenceController::serialBoardWrite(int boardId, const QString &atCmd, bool endOfLine)
{
    int commPortID = -1;

    // Identificar a placa e obter o ID da porta de comunicação associada
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            commPortID = boardInfo->getCommPortIdentification();
            break;
        }
    }

    // Se um ID de porta válido foi encontrado, escreva para a porta serial
    if (commPortID != -1) {
        serialWrite(commPortID, atCmd, endOfLine);
    } else {
        qDebug() << "Board ID not found or no communication port ID associated with this board.";
    }
}

void PersistenceController::closeConnection(int portId)
{
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

void PersistenceController::closeBoardConnection(int boardId)
{
    for(Board* boardInfo: boardList){
        //Board found
        if(boardInfo->getBoardIdentification()==boardId){
            closeConnection(boardInfo->getCommPortIdentification());
            qDebug() << "Connection closed for board ID" << boardId;
            return;
        }
    }
    qDebug() << "Board ID" << boardId << "not found.";
}

QString PersistenceController::serialRead(int portId) {
    // Cria um objeto QRegularExpression estático para ser reutilizado.
    // Isso evita a recompilação da expressão regular em cada chamada da função.
    static QRegularExpression newLineRegex("[\\r\\n]");

    // Verifica se o ID da porta está dentro do intervalo válido.
    if (portId < 0 || portId >= serialComm.size()) {
        qDebug() << "ID da porta está fora do intervalo.";
            return QString();
    }

    QSerialPort* port = serialComm[portId];
    // Verifica se a porta está aberta antes de tentar ler.
    if (!port->isOpen()) {
        qDebug() << "Porta não está aberta.";
        return QString();
    }

    QByteArray newData;
    QString recvStr;

    // Espera até 100 milissegundos para que dados estejam prontos para serem lidos.
    if (port->waitForReadyRead(100)) {
        // Lê todos os dados disponíveis na porta serial.
        newData = port->readAll();
        // Converte os dados binários para uma string UTF-8.
        recvStr = QString::fromUtf8(newData);
        // Remove caracteres de nova linha usando a expressão regular pré-compilada.
        recvStr.remove(newLineRegex);
    } else {
        qDebug() << "Timeout na leitura ou nenhum dado disponível.";
    }

    return recvStr;
}

QString PersistenceController::serialBoardRead(int boardId) {
    int commPortID = -1;

    // Identifica a placa e obtém o ID da porta de comunicação associada
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            commPortID = boardInfo->getCommPortIdentification();
            break;
        }
    }

    // Verifica se um ID de porta válido foi encontrado
    if (commPortID != -1) {
        return serialRead(commPortID);
    } else {
        qDebug() << "Board ID" << boardId << "not found or no communication port ID associated with this board.";
        return QString(); // Retorna uma QString vazia se nenhum ID válido foi encontrado
    }
}

int PersistenceController::writeFirmware(const QString& cmdStr) {
    int exitCode = 1; // Código de saída padrão para erro
    QString line;
    QProcess process;

    // Configurando o comando a ser executado
    QStringList args;
    args << "/c" << cmdStr;
    process.start("cmd.exe", args);

    if (!process.waitForStarted()) {
        qDebug() << "Falha ao iniciar o processo.";
        return exitCode;
    }

    qDebug() << "##########################################################################";
    addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, "Iniciando o Programa AVRDUDE...", true);

    // Espera o processo terminar
    if (!process.waitForFinished(-1)) { // -1 para esperar indefinidamente
        qDebug() << "Processo não finalizado corretamente.";
            return exitCode;
    }

    // Lê a saída de erro padrão
    QString stdError = process.readAllStandardError();
    QStringList errorLines = stdError.split('\n');

    for (const QString& errorLine : errorLines) {
        if (!errorLine.isEmpty()) {
            QString cleanedLine = errorLine.trimmed();
            addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, cleanedLine, false);
        }
    }

    exitCode = process.exitCode();
    qDebug() << "##########################################################################";
    qDebug() << "Exited with error code : " << exitCode ;
    addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, "Finalizando o Programa AVRDUDE...", true);

    if (exitCode == 0) {
        line = "Atualização de firmware realizada com sucesso!";
    } else {
        line = "Erro na atualização de firmware!";
    }

    addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, line, true);
    qDebug() << line;

    return exitCode;
}

void PersistenceController::setBoardInformation(int index, int boardId) {
    // Verifica se o índice da porta está dentro do intervalo válido.
    if (index < 0 || index >= serialComm.size()) {
        qDebug() << "Índice da porta está fora do intervalo.";
        return;
    }

    // Itera sobre a lista de placas para encontrar a placa com o ID especificado.
    for (Board* boardInfo : boardList) {
        if (boardInfo->getBoardIdentification() == boardId) {
            // Define a identificação da porta de comunicação para a placa encontrada.
            boardInfo->setCommPortIdentification(index);

            // Define o nome da porta de comunicação, que é obtido a partir da lista serialComm.
            boardInfo->setCommPortName(serialComm[index]->portName());

            qDebug() << "Informação da placa atualizada com sucesso.";
            return;  // Finaliza a função após a atualização da placa.
        }
    }

    // Se o loop terminar sem encontrar uma placa correspondente, loga uma mensagem de erro.
    qDebug() << "ID da placa" << boardId << "não encontrado.";
}

void PersistenceController::addCmdTestMessage(int testId, int boardId, const QString& testMessage, bool header) {
    QString strMessage;

    // Usa um switch para lidar com diferentes tipos de mensagens de teste.
    switch (testId) {
    case JigaTestConstants::FIRMWARE_UPLOAD:
        if (header) {
            strMessage = QString(CmdMessageConstants::CMD_HDR_FIRM_UPLOAD) + " ";
        }
        strMessage += testMessage; // Concatena a mensagem de teste ao cabeçalho se necessário.
        fwUpdateModel->addTestMessage(boardId, strMessage);
        break;

    default:
        qDebug() << "Test ID not recognized:" << testId;
        break;
    }
}

void PersistenceController::setReportProperty(const QString &key, const QString &value) {
    reportProperties[key] = value;  // Define a propriedade no QMap
}

QString PersistenceController::getReportProperty(const QString &key) const {
    return reportProperties.value(key);  // Retorna o valor associado à chave
}

