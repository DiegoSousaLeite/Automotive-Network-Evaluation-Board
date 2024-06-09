#ifndef BUSINESSCONTROLLER_H
#define BUSINESSCONTROLLER_H

#include <QObject>
#include <QList>
#include <QThread>
#include "Board.h"
#include "PersistenceController.h"
#include "EcuBusinessInterface.h"
#include "McuBusinessInterface.h"
#include "CommunicationTest.h"
#include "FirmwareUpload.h"
#include "DigitalInputTest.h"
#include "AnalogInputTest.h"
#include "AnalogOutputTest.h"
#include "CANInitTest.h"
#include "LoopbackCanTest.h"
#include "CAN1NetworkTest.h"
#include "CAN2NetworkTest.h"
#include "LinNetworkTest.h"
#include "MCUInterfaceTest.h"
#include <QEventLoop>
#include <QTimer>
#include <QStringView>


class BusinessController : public QObject,public virtual McuBusinessInterface, public virtual EcuBusinessInterface {
    Q_OBJECT

public:
    explicit BusinessController(QObject *parent = nullptr);
    void setPersistenceController(PersistenceController *controller);

    CommunicationTest *commTestModel;
    FirmwareUpload *fwUploadModel;
    DigitalInputTest *diInputModel;
    AnalogInputTest *anInputModel;
    AnalogOutputTest *anOutputModel;
    CANInitTest *canInitModel;
    LoopbackCanTest *lbNetworkModel;
    CAN1NetworkTest *c1NetworkModel;
    CAN2NetworkTest *c2NetworkModel;
    LinNetworkTest *lnNetworkModel;
    MCUInterfaceTest *mcu1InterModel;
    QList<Board *> boardList;
    PersistenceController *psController;

    void addCmdTestMessage(int testId, int boardId, const QString &testMessage, bool header) override;
private:

protected:
    void sendAtCommand(int testId, int boardId, const QString &atCommand);
    bool acknowledgeAtCommand(int testId, int boardId);
    int getTestReportCode(const QString &recvStr);


};

#endif // BUSINESSCONTROLLER_H
