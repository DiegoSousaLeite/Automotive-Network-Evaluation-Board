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
#include "UtilsConversion.h"
#include <QThread>

class PersistenceController : public QObject {
    Q_OBJECT

public:
    static PersistenceController* getInstance();
    virtual ~PersistenceController();

    int findSerialCommPorts();
    QVector<SerialCommPort*> getSerialCommPortInfo();
    void setCommPortFound(int index, int commPortId);
    int getCommPortFound(int index) const;
    bool loadUsbProgrammer();
    bool openConnection(int portId, int baudRate);
    bool openBoardConnection(int boardId,int baudRate);
    bool openBoardConnection(int boardId);
    QString getSystemPortDescription(int index);
    QString getPortDescription(int index);
    QString getDescriptivePortName(int index);
    QString getBoardCommPort(int boardId);
    QString getBoardDescription(int boardId);
    int getTotalNumberOfPorts();

    void serialWrite(int port_id,const QString& atCmd, bool endOfLine);



private:
    explicit PersistenceController(QObject *parent = nullptr);
    static PersistenceController* instance;
    libusb_context *usbContext = nullptr;

    libusb_device* findUsbDevice(libusb_device** devices, uint16_t vid, uint16_t pid);



    QList<Board*> boardList;
    FirmwareUpload* fwUpdateModel;

    libusb_device* usbDevice; // USB device member

    std::vector<QSerialPort*> serialComm;
    QVector<int> foundCommPorts; // Armazena os índices das portas encontradas

signals:
    void deviceFound();
    void deviceNotFound();

};

#endif // PERSISTENCECONTROLLER_H
