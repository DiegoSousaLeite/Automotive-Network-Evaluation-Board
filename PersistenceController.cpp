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
    uint16_t vid = static_cast<uint16_t>(UtilsConversion::hexToShort(QString::fromStdString(getenv(SystemProperties::MCU_PROG_VID))));
    uint16_t pid = static_cast<uint16_t>(UtilsConversion::hexToShort(QString::fromStdString(getenv(SystemProperties::MCU_PROG_PID))));

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
