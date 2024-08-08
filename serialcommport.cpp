#include "SerialCommPort.h"
#include <iostream>

// Função de inicialização
void SerialCommPort::init() {
    port_id = ErrorCodeInterface::ERR_INVALID_PORT;
    portDesc = "Serial CommPort not found";
    descPortName = "";
    systemPortName = "";
    portLocation = "";
    vid = -1;
    pid = -1;
    portLocLastId = -1;
}

// Construtor padrão
SerialCommPort::SerialCommPort() {
    init();
}

// Construtor com QSerialPortInfo e port_id
SerialCommPort::SerialCommPort(QSerialPortInfo& serialPort, int port_id) {
    qDebug() << "Colocando o portID no construtor do SerialCommPort: " << port_id;
    this->port_id = port_id;
    this->portDesc = serialPort.portName();
    this->descPortName = serialPort.portName();
    this->systemPortName = serialPort.systemLocation();
    this->portLocation = serialPort.portName();
    // Verificação adicional para garantir que o último caractere é um dígito
    QString lastChar = portLocation.right(1);
    bool ok;
    int lastId = lastChar.toInt(&ok);

    if (ok) {
        this->portLocLastId = lastId;
        qDebug() << "Último caractere como inteiro:" << lastId;
    } else {
        qWarning() << "O último caractere da portLocation não é um dígito: " << portLocation;
        this->portLocLastId = -1; // ou algum valor padrão de erro
    }
    this->vid = serialPort.vendorIdentifier();
    this->pid = serialPort.productIdentifier();

}

// Construtor com portId e portDescription
SerialCommPort::SerialCommPort(int portId, QString portDescription) {
    this->port_id = portId;
    this->portDesc = portDescription;
}

void SerialCommPort::setCommPortId(int portId) {
    this->port_id = portId;
}

int SerialCommPort::getCommPortId() const {
    return this->port_id;
}

void SerialCommPort::setPortDescription(QString portDescription) {
    this->portDesc = portDescription;
}

QString SerialCommPort::getPortDescription() const {
    return this->portDesc;
}

void SerialCommPort::setDescriptivePortName(QString descPortName) {
    this->descPortName = descPortName;
}

QString SerialCommPort::getDescriptivePortName() const {
    return this->descPortName;
}

void SerialCommPort::setSystemPortName(QString systemPortName) {
    this->systemPortName = systemPortName;
}

QString SerialCommPort::getSystemPortName() const {
    return this->systemPortName;
}

void SerialCommPort::setLocation(QString location) {
    this->portLocation = location;
    this->portLocLastId = location.right(1).toInt();
}

QString SerialCommPort::getLocation() const {
    return this->portLocation;
}

void SerialCommPort::setVendorID(int vid) {
    this->vid = vid;
}

int SerialCommPort::getVendorID() const {
    return this->vid;
}

void SerialCommPort::setProductID(int pid) {
    this->pid = pid;
}

int SerialCommPort::getProductID() const {
    return this->pid;
}

int SerialCommPort::getPortLocationIndex() const {
    return this->portLocLastId;
}

void SerialCommPort::printSerialCommPortInfo() const {
    std::cout << " [" << port_id << "] ";
    std::cout << "(" << systemPortName.toStdString() << "): ";
    std::cout << descPortName.toStdString() << " - ";
    std::cout << portDesc.toStdString() << " @ ";
    std::cout << portLocation.toStdString();
    std::cout << " (VID = " << vid << ", ";
    std::cout << "PID = " << pid << ")" << std::endl;
}

QString SerialCommPort::toString() const {
    QString commPortInfo = "[" + QString::number(getCommPortId()) + "] " + getSystemPortName() + " : " + getDescriptivePortName() + " : " + getPortDescription();
    return commPortInfo;
}

void SerialCommPort::setSerialCommPort(QSerialPortInfo& serialPort, int port_id) {
    this->port_id = port_id;
    this->portDesc = serialPort.portName();
    this->descPortName = serialPort.portName();
    this->systemPortName = serialPort.systemLocation();
    this->portLocation = serialPort.portName();
    this->portLocLastId = portLocation.right(1).toInt();
    this->vid = serialPort.vendorIdentifier();
    this->pid = serialPort.productIdentifier();
}
