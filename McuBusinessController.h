#ifndef MCUBUSINESSCONTROLLER_H
#define MCUBUSINESSCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include "PersistenceController.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "CmdMessageConstants.h"
#include "EcuBusinessInterface.h"
#include "atCommandConstants.h"
#include "BusinessController.h"
#include <QSettings>
#include <QCoreApplication>
#include "McuBusinessInterface.h"
#include <stdexcept>

class McuBusinessController : public BusinessController {
    Q_OBJECT

public:
    explicit McuBusinessController(QObject *parent = nullptr);
    bool loadProgrammer(int programmerId);
    int getSerialProgrammerMode();
    void setSerialProgrammerMode(int progMode);
    int uploadFirmware(int programmerId);
    bool setCanBus1Network();
    bool setCanBus2Network();

private:
    QSerialPort serialPort;
    QTimer delayTimer;

    bool loadUsbProgrammer();
    bool loadSerialProgrammer();


protected:
    int checkCanBus1Network(int testId);

};

#endif // MCUBUSINESSCONTROLLER_H
