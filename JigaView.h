#ifndef JIGAVIEW_H
#define JIGAVIEW_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include "EcuFrameController.h"
#include "McuFrameController.h"
#include "MainMenu.h"
#include "AnalogOutputMenu.h"
#include "CAN1NetworkMenu.h"
#include "CAN2NetworkMenu.h"
#include "CANInitMenu.h"
#include "CANLoopbackMenu.h"
#include "CommunicationMenu.h"
#include "DigitalInputMenu.h"
#include "EcuUploadMenu.h"
#include "LINNetworkMenu.h"
#include "LoadSerialPortsMenu.h"
#include "MCUInterfaceMenu.h"
#include "McuUploadMenu.h"
#include "ReportTestMenus.h"
#include "AnalogInputMenu.h"

//class EcuFrameController;
//class McuFrameController;

class JigaView : public QObject
{
    Q_OBJECT

public:
    explicit JigaView(QObject *parent = nullptr);
    void setEcuFrameController(EcuFrameController *controller);
    void setMcuFrameController(McuFrameController *controller);
    void start();

    MainMenu *mainMenu;
    AnalogInputMenu *anInputMenu;
    AnalogOutputMenu *anOutputMenu;
    CAN1NetworkMenu *c1NetworkMenu;
    CAN2NetworkMenu *c2NetworkMenu;
    CANInitMenu *cInitMenu;
    CANLoopbackMenu *cLoopbackMenu;
    CommunicationMenu *commMenu;
    DigitalInputMenu *diInputMenu;
    EcuUploadMenu *ecuUploadMenu;
    LINNetworkMenu *lnNetworkMenu;
    LoadSerialPortsMenu *loadSerialPortMenu;
    MCUInterfaceMenu *mcuInterfaceMenu;
    McuUploadMenu *mcuUploadMenu;
    ReportTestMenus *repTestMenu;

private:
    void selectCommunicationTest();
    void selectMcuInterfaceTest();
    void selectDigitalInputTest();
    void selectAnalogInputTest();
    void selectAnalogOutputTest();
    void selectCanInitTest();
    void selectLoopbackCanTest();
    void selectCan1NetworkTest();
    void selectCan2NetworkTest();
    void selectLinNetworkTest();
    void selectFirmwareUpload();
    void selectExecuteAllTests();
    void selectReportTest();
    void selectLoadSerialPortTest();

    void startCommunicationTest(int boardId);
    void startMCUInterfaceTest(int testId);
    void startDigitalInputTest(int boardId);
    void startAnalogInputTest(int boardId);
    void startCan1NetworkTest(int testId);
    void startCanLoopbackTest(int boardId);
    void startCan2NetworkTest();
    void startMcuFirmwareUpload();
    void startEcuFirmwareUpload(int boardId, int processorId);
    void startCanInitTest(int boardId);
    void selectEcuProcessor(int boardId);

    EcuFrameController *ecuFmController;
    McuFrameController *mcuFmController;
};

#endif // JIGAVIEW_H
