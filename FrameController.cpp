#include "FrameController.h"
#include <QTimer>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(lcFrameController, "controller.frame")

FrameController::FrameController(QObject *parent) : QObject(parent) {
    // Inicialização dos modelos

    commTestModel = CommunicationTest::getInstance();
    diInputModel = DigitalInputTest::getInstance();
    anInputModel = AnalogInputTest::getInstance();
    anOutputModel = AnalogOutputTest::getInstance();
    canInitModel = CANInitTest::getInstance();
    lbNetworkModel = LoopbackCanTest::getInstance();
    c1NetworkModel = CAN1NetworkTest::getInstance();
    c2NetworkModel = CAN2NetworkTest::getInstance();
    lnNetworkModel = LinNetworkTest::getInstance();
    fwUpdateModel = FirmwareUpload::getInstance();
    mcu1TestModel = MCUInterfaceTest::getInstance();

}

FrameController::~FrameController() {
    // Destruição apropriada, se necessário
}

void FrameController::resetTestModel(int test_id) {
    switch (test_id) {
    case JigaTestConstants::COMMUNICATION_TEST:
        commTestModel->resetTestModel();
        break;
    case JigaTestConstants::DIGITAL_INPUT_TEST:
        diInputModel->resetTestModel();
        break;
    case JigaTestConstants::ANALOG_INPUT_TEST:
        anInputModel->resetTestModel();
        break;
    case JigaTestConstants::ANALOG_OUTPUT_TEST:
        anOutputModel->resetTestModel();
        break;
    case JigaTestConstants::CAN_INIT_TEST:
        canInitModel->resetTestModel();
        break;
    case JigaTestConstants::LOOPBACK_CAN_TEST:
        lbNetworkModel->resetTestModel();
        break;
    case JigaTestConstants::CAN1_NETWORK_TEST:
        c1NetworkModel->resetTestModel();
        break;
    case JigaTestConstants::CAN2_NETWORK_TEST:
        c2NetworkModel->resetTestModel();
        break;
    case JigaTestConstants::LIN_NETWORK_TEST:
        lnNetworkModel->resetTestModel();
        break;
    case JigaTestConstants::FIRMWARE_UPLOAD:
        fwUpdateModel->resetTestModel();
        break;
    case JigaTestConstants::MCU_RST_ACT_TEST:
    case JigaTestConstants::MCU_RST_DAC_TEST:
    case JigaTestConstants::MCU_IDENT_PORT_TEST:
    case JigaTestConstants::MCU_SEL_CANBUS1_TEST:
    case JigaTestConstants::MCU_SEL_CANBUS2_TEST:
    case JigaTestConstants::MCU_GET_CANBUS_TEST:
    case JigaTestConstants::MCU_TOG_ECU3BUS_TEST:
    case JigaTestConstants::MCU_TOG_ECU4BUS_TEST:{
        mcu1TestModel->resetTestModel();
        break;
    }
    default:
        break;
    }
}

void FrameController::addHeaderTestMessage(int test_id, int board_id, const QString &testMessage) {
    QString strMessage;

    switch(test_id) {
    case JigaTestConstants::COMMUNICATION_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_COMMUNICATION).arg(CmdMessageConstants::CMD_MSG_COMMUNICATION) + testMessage;
        commTestModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::DIGITAL_INPUT_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_DIGITAL_INPUT).arg(CmdMessageConstants::CMD_MSG_DIGITAL_INPUT) + testMessage;
        diInputModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::ANALOG_INPUT_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_ANALOG_INPUT).arg(CmdMessageConstants::CMD_MSG_ANALOG_INPUT) + testMessage;
        anInputModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::ANALOG_OUTPUT_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_ANALOG_OUTPUT).arg(CmdMessageConstants::CMD_MSG_ANALOG_OUTPUT) + testMessage;
        anOutputModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::CAN_INIT_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_CAN_INIT).arg(CmdMessageConstants::CMD_MSG_CAN_INIT) + testMessage;
        canInitModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::LOOPBACK_CAN_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_LOOPBACK_CAN).arg(CmdMessageConstants::CMD_MSG_LOOPBACK_CAN) + testMessage;
        lbNetworkModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::CAN1_NETWORK_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_CAN1_NETWORK).arg(CmdMessageConstants::CMD_MSG_CAN1_NETWORK) + testMessage;
        c1NetworkModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::CAN2_NETWORK_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_CAN2_NETWORK).arg(CmdMessageConstants::CMD_MSG_CAN2_NETWORK) + testMessage;
        c2NetworkModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::LIN_NETWORK_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_LIN_NETWORK).arg(CmdMessageConstants::CMD_MSG_LIN_NETWORK) + testMessage;
        lnNetworkModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::FIRMWARE_UPLOAD:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_FIRM_UPLOAD).arg(CmdMessageConstants::CMD_MSG_FIRM_UPDATE) + testMessage;
        fwUpdateModel->addTestMessage(board_id, strMessage);
        break;
    case JigaTestConstants::MCU_RST_ACT_TEST:
    case JigaTestConstants::MCU_RST_DAC_TEST:
    case JigaTestConstants::MCU_IDENT_PORT_TEST:
    case JigaTestConstants::MCU_SEL_CANBUS1_TEST:
    case JigaTestConstants::MCU_SEL_CANBUS2_TEST:
        strMessage = QString("%1 %2").arg(CmdMessageConstants::CMD_HDR_MCU_INTERFACE).arg(CmdMessageConstants::CMD_MSG_MCU_INTERFACE) + testMessage;
        mcu1TestModel->addTestMessage(board_id, strMessage);
        break;
    default:
        qWarning(lcFrameController) << "Unknown test ID:" << test_id;
        break;
    }
}


void FrameController::waitReportTestTimeout(int test_id, int offset) {
    // Implementação usando QTimer
}

/*
void FrameController::addFrameView(RCFrame *jigaFrame) {
    this->jigaFrame = jigaFrame;
}
*/
void FrameController::setReportController(ReportControllerInterface *rpController) {
    this->rpController = rpController;
}

// Mais definições de métodos conforme necessário
