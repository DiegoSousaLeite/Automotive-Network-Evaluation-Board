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


libusb_device* PersistenceController::findUsbDevice(libusb_device** devices, uint16_t vid, uint16_t pid) {
    for (int i = 0; devices[i] != nullptr; i++) {
        libusb_device* device = devices[i];
        libusb_device_descriptor descriptor;

        if (libusb_get_device_descriptor(device, &descriptor) == 0) {
            if (descriptor.idVendor == vid && descriptor.idProduct == pid) {
                emit deviceFound();
                return device;
            }
        }

        if (descriptor.bDeviceClass == LIBUSB_CLASS_HUB) {
            libusb_device** childDevices;
            int count = libusb_get_device_list(usbContext, &childDevices); // Use usbContext
            if (count < 0) continue;

            libusb_device* found = findUsbDevice(childDevices, vid, pid);
            libusb_free_device_list(childDevices, 1);
            if (found) {
                emit deviceFound();
                return found;
            }
        }
    }

    emit deviceNotFound();
    return nullptr;
}

int PersistenceController::findSerialCommPorts() {

    int portFounds = 0;
    int i;

    // Obter descrições de configuração
    QString ecuPortDesc = QString::fromStdString(getenv(SystemProperties::ECU_PORT_DESCRIPTION));
    QString ecuDescPortName = QString::fromStdString(getenv(SystemProperties::ECU_DESC_PORT_NAME));
    QString mcuPortDesc = QString::fromStdString(getenv(SystemProperties::MCU_PORT_DESCRIPTION));
    QString mcuDescPortName = QString::fromStdString(getenv(SystemProperties::MCU_DESC_PORT_NAME));

    // Lista de portas disponíveis
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    // Verificar se alguma porta foi encontrada
    if (availablePorts.isEmpty()) {
        return 0;
    }

    // Verificar cada porta disponível
    for (i = 0; i < availablePorts.count(); ++i) {
        QSerialPortInfo portInfo = availablePorts[i];
        QString portDescription = portInfo.description();
        QString portName = portInfo.portName();

        if (portDescription.startsWith(ecuPortDesc) || portDescription.startsWith(mcuPortDesc)) {
            foundCommPorts.append(i);
            portFounds++;
            continue;
        }

        if (portName.startsWith(ecuDescPortName) || portName.startsWith(mcuDescPortName)) {
            foundCommPorts.append(i);
            portFounds++;
        }
    }

    this->foundCommPorts.append(i); // Adiciona o índice da porta encontrada ao vetor


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
    libusb_device **devs;
    libusb_device *found = nullptr;
    libusb_context *ctx = nullptr;
    int r; // Para resultados das chamadas de função
    ssize_t cnt; // Número de dispositivos na lista

    // Inicialize o contexto da libusb
    r = libusb_init(&ctx);
    if (r < 0) {
        qCWarning(usb) << "Init Error" << r;
        return false;
    }

    // Obtenha a lista de dispositivos
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        qCWarning(usb) << "Get Device List Error";
        libusb_exit(ctx);
        return false;
    }

    // Converta VID e PID de strings ou configuração para números
    uint16_t vid = UtilsConversion::hexToShort(QString::fromStdString(getenv(SystemProperties::MCU_PROG_VID)));
    uint16_t pid = UtilsConversion::hexToShort(QString::fromStdString(getenv(SystemProperties::MCU_PROG_PID)));

    // Tente encontrar o dispositivo
    found = findUsbDevice(devs, vid, pid);

    // Libere a lista de dispositivos
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);

    if (found) {
        usbDevice = found; // Armazene o dispositivo encontrado globalmente ou como membro da classe
        qCDebug(usb) << "Device Found";
        return true;
    } else {
        qCDebug(usb) << "Device Not Found";
        return false;
    }
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




