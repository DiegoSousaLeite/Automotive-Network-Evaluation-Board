#ifndef SERIALCOMMPORT_H
#define SERIALCOMMPORT_H

#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "ErrorCodeInterface.h"
#include <QDebug>
#include <QString>

class SerialCommPort {
private:
    int port_id;
    QString portDesc;
    QString descPortName;
    QString systemPortName;
    QString portLocation;
    int vid;
    int pid;
    int portLocLastId;



public:
    SerialCommPort();
    SerialCommPort(QSerialPortInfo& serialPort, int port_id);
    SerialCommPort(int portId, QString portDescription);

    void setCommPortId(int portId);
    int getCommPortId() const;

    void setPortDescription(QString portDescription);
    QString getPortDescription() const;

    void setDescriptivePortName(QString descPortName);
    QString getDescriptivePortName() const;

    void setSystemPortName(QString systemPortName);
    QString getSystemPortName() const;

    void setLocation(QString location);
    QString getLocation() const;

    void setVendorID(int vid);
    int getVendorID() const;

    void setProductID(int pid);
    int getProductID() const;

    int getPortLocationIndex() const;

    void printSerialCommPortInfo() const;
    QString toString() const;

    void setSerialCommPort(QSerialPortInfo& serialPort, int port_id);

    void init();
};

#endif // SERIALCOMMPORT_H
