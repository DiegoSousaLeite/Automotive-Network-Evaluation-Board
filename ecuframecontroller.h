#ifndef ECUFRAMECONTROLLER_H
#define ECUFRAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include "FrameController.h"
#include "CmdMessageConstants.h"
#include "ErrorCodeInterface.h"
#include "EcuBusinessInterface.h"
#include "SerialCommPort.h"
#include "ReportControllerInterface.h"

class EcuFrameController : public FrameController {
    Q_OBJECT

public:
    explicit EcuFrameController(QObject *parent = nullptr);
    ~EcuFrameController();

    void executeTest(int test_id, int board_id);
    void executeTest(int test_id);
    void executeTestReport(int test_id);
    void executeCommunicationTest();
    void executeCan1NetworkTest();
    void executeCan2NetworkTest();
    void executeDigitalInputTest();
    void executeAnalogOutputTest();
    void executeLinNetworkTest();
    void executeCanInitTest();
    void executeLoopbackCanTest();
    void executeAnalogInputTest();

    void executeFirmwareUpload(int board_id);
    void executeFirmwareUpload(int port_id, const QString &pathToHexFile);
    void setEcuBusinessController(EcuBusinessInterface bsInterface);

signals:
    void testStarted(int test_id, int board_id, const QString &message);
    void testFinished(int test_id, int board_id, const QString &message);
    void errorOccurred(int test_id, int board_id, const QString &error);

private slots:
    void handleTimeout(); // Handles what happens when a test timeout occurs

private:
    EcuBusinessInterface* bsController;

    void setupModels();
    void resetTestModel(int test_id);
    void addHeaderTestMessage(int test_id, int board_id, const QString &testMessage);
    void waitReportTestTimeOut(int test_id, int offset, int board_id);

    // Example of member variables if needed
    QTimer timer;
};

#endif // ECUFRAMECONTROLLER_H
