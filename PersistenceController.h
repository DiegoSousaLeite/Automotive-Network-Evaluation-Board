#ifndef PERSISTENCECONTROLLER_H
#define PERSISTENCECONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMap>
#include <vector>
#include "FirmwareUpload.h"
#include "Board.h"
#include "Ecu1Board.h"
#include "Ecu2Board.h"
#include "Ecu3Board.h"
#include "Ecu4Board.h"
#include "Mcu1Board.h"
#include <libusb.h>
#include "SystemProperties.h"

class PersistenceController : public QObject {
    Q_OBJECT

public:
    static PersistenceController* getInstance();
    virtual ~PersistenceController();

    int findSerialCommPorts();
    QList<QSerialPortInfo> getSerialCommPortInfo();
    bool openConnection(int portId, int baudRate);
    bool openBoardConnection(int boardId,int baudRate);
    void closeConnection(const QString &portName);
    void closeBoardConnection(int boardId);

    bool loadUsbProgrammer();
    QString readFromSerial(const QString &portName);
    void writeToSerial(const QString &portName, const QString &data, bool endOfLine);
    int writeFirmware(const QString &cmdStr);



private:
    explicit PersistenceController(QObject *parent = nullptr);
    static PersistenceController* instance;
    libusb_context *usbContext = nullptr;

   libusb_device* findUsbDevice(libusb_device** devices, uint16_t vid, uint16_t pid);

    QList<Board*> boardList;
    FirmwareUpload* fwUpdateModel;

    std::vector<QSerialPort*> serialComm;
    QVector<int> foundCommPorts; // Armazena os índices das portas encontradas

signals:
    void deviceFound();
    void deviceNotFound();
};

#endif // PERSISTENCECONTROLLER_H
