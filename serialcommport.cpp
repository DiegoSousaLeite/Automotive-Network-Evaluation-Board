#include "serialcommport.h"
#include <QDebug>

SerialCommPort::SerialCommPort(QObject *parent)
    : QObject(parent), commPortID(-1), portDescription(""), descPortName(""), systemPortName("")
{
}

SerialCommPort::SerialCommPort(int portId, const QString &portDescription, QObject *parent)
    : QObject(parent), commPortID(portId), portDescription(portDescription)
{
}

int SerialCommPort::getCommPortId() const {
    return commPortID;
}

void SerialCommPort::setCommPortId(int portId) {
    commPortID = portId;
}

QString SerialCommPort::getPortDescription() const {
    return portDescription;
}

void SerialCommPort::setPortDescription(const QString &portDescription) {
    this->portDescription = portDescription;
}

QString SerialCommPort::getDescriptivePortName() const {
    return descPortName;
}

void SerialCommPort::setDescriptivePortName(const QString &descPortName) {
    this->descPortName = descPortName;
}

QString SerialCommPort::getSystemPortName() const {
    return systemPortName;
}

void SerialCommPort::setSystemPortName(const QString &systemPortName) {
    this->systemPortName = systemPortName;
}

void SerialCommPort::printSerialCommPortInfo() const {
    qDebug() << QString("[%1] : (%2 : %3 : %4)")
                    .arg(getCommPortId())
                    .arg(getSystemPortName())
                    .arg(getDescriptivePortName())
                    .arg(getPortDescription());
}

QString SerialCommPort::toString() const {
    return QString("[%1] %2 : %3 : %4")
        .arg(getCommPortId())
        .arg(getSystemPortName())
        .arg(getDescriptivePortName())
        .arg(getPortDescription());
}
