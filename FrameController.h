#ifndef FRAMECONTROLLER_H
#define FRAMECONTROLLER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "JigaTestInterface.h"
#include "CmdMessageConstants.h"
#include "ReportControllerInterface.h"
#include "TestReportModel.h"
#include "AnalogInputTest.h"
#include "AnalogOutputTest.h"
#include "CAN1NetworkTest.h"
#include "CAN2NetworkTest.h"
#include "CommunicationTest.h"
#include "DigitalInputTest.h"
#include "FirmwareUpload.h"
#include "LinNetworkTest.h"
#include "LoopbackCanTest.h"
#include "MCUInterfaceTest.h"
#include "CANInitTest.h"
#include "IFrameListener.h"
#include "PropertyChangeListener.h"



class FrameController : public QObject,public IFrameListener {
    Q_OBJECT

public:
    explicit FrameController(QObject *parent = nullptr);
    virtual ~FrameController();

    CommunicationTest *commTestModel;
    DigitalInputTest *diInputModel;
    AnalogInputTest *anInputModel;
    AnalogOutputTest *anOutputModel;
    CANInitTest *canInitModel;
    LoopbackCanTest *lbNetworkModel;
    CAN1NetworkTest *c1NetworkModel;
    CAN2NetworkTest *c2NetworkModel;
    LinNetworkTest *lnNetworkModel;
    FirmwareUpload *fwUpdateModel;
    MCUInterfaceTest *mcu1TestModel;

    void addChangeListener(IFrameListener* listener) override;
    void removeChangeListener(IFrameListener* listener) override;

protected:
    void resetTestModel(int test_id);
    void addHeaderTestMessage(int test_id, int board_id, const QString &testMessage);
    void waitReportTestTimeout(int test_id, int offset);
    virtual void executeFirmwareUpload(int board_id) = 0;
    // void addFrameView(RCFrame *jigaFrame);
    void setReportController(ReportControllerInterface *rpController);
    ReportControllerInterface *rpController;
    //RCFrame *jigaFrame;
    void handleTimeout();

    void addTestReportModels(const QList<TestReportModel*>& models);

private:
    QList<IFrameListener*> listeners;


public slots:
    void onReportUpdated(const QString &message);

protected slots:
    virtual void propertyChange() = 0;
};

#endif // FRAMECONTROLLER_H
