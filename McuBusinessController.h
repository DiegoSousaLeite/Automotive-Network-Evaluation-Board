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

class McuBusinessController : public BusinessController {
    Q_OBJECT

public:
    explicit McuBusinessController(QObject *parent = nullptr);
    bool loadProgrammer(int programmerId);
    int uploadFirmware(int programmerId);
    bool setCanBus1Network();

private:
    QSerialPort serialPort;
    QTimer delayTimer;

    bool loadUsbProgrammer();
    bool loadSerialProgrammer();
    int getSerialProgrammerMode();
    void setSerialProgrammerMode(int progMode);
    int checkCanBus1Network(int testId);
    void sendAtCommand(int testId, int boardId, const QString &command);
    bool acknowledgeAtCommand(int testId, int boardId);

signals:
    void errorOccurred(const QString &error);
    void messageLogged(const QString &message);

};

#endif // MCUBUSINESSCONTROLLER_H
