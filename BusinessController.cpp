#include "BusinessController.h"
#include "atCommandConstants.h"

BusinessController::BusinessController(QObject *parent) : QObject(parent) {
    // Initializing models
    commTestModel = CommunicationTest::getInstance();
    fwUploadModel =  FirmwareUpload::getInstance();
    diInputModel =  DigitalInputTest::getInstance();
    anInputModel =  AnalogInputTest::getInstance();
    anOutputModel =  AnalogOutputTest::getInstance();
    canInitModel =  CANInitTest::getInstance();
    lbNetworkModel =  LoopbackCanTest::getInstance();
    c1NetworkModel =  CAN1NetworkTest::getInstance();
    c2NetworkModel =  CAN2NetworkTest::getInstance();
    lnNetworkModel =  LinNetworkTest::getInstance();
    mcu1InterModel =  MCUInterfaceTest::getInstance();
}

void BusinessController::setPersistenceController(PersistenceController *controller)
{
    psController = controller;
}

void BusinessController::addCmdTestMessage(int testId, int boardId, const QString &testMessage, bool header) {

        QString strMessage = "";

        switch (testId) {
        case JigaTestConstants::COMMUNICATION_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_COMMUNICATION) + " ";
            }
            strMessage += testMessage;
            commTestModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::DIGITAL_INPUT_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_DIGITAL_INPUT) + " ";
            }
            strMessage += testMessage;
            diInputModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::ANALOG_INPUT_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_ANALOG_INPUT) + " ";
            }
            strMessage += testMessage;
            anInputModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::ANALOG_OUTPUT_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_ANALOG_OUTPUT) + " ";
            }
            strMessage += testMessage;
            anOutputModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::CAN_INIT_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_CAN_INIT) + " ";
            }
            strMessage += testMessage;
            canInitModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::LOOPBACK_CAN_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_LOOPBACK_CAN) + " ";
            }
            strMessage += testMessage;
            lbNetworkModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::CAN1_NETWORK_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_CAN1_NETWORK) + " ";
            }
            strMessage += testMessage;
            c1NetworkModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::CAN2_NETWORK_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_CAN2_NETWORK) + " ";
            }
            strMessage += testMessage;
            c2NetworkModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::LIN_NETWORK_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_LIN_NETWORK) + " ";
            }
            strMessage += testMessage;
            lnNetworkModel->addTestMessage(boardId, strMessage);
            break;
        case JigaTestConstants::FIRMWARE_UPLOAD:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_FIRM_UPLOAD) + " ";
            }
            strMessage += testMessage;
            fwUploadModel->addTestMessage(boardId, strMessage);
            break;
        // Add cases for MCU specific tests as well
        case JigaTestConstants::MCU_RST_ACT_TEST:
        case JigaTestConstants::MCU_RST_DAC_TEST:
        case JigaTestConstants::MCU_RST_ATT_TEST:
        case JigaTestConstants::MCU_IDENT_PORT_TEST:
        case JigaTestConstants::MCU_SEL_CANBUS1_TEST:
        case JigaTestConstants::MCU_SEL_CANBUS2_TEST:
        case JigaTestConstants::MCU_GET_CANBUS_TEST:
        case JigaTestConstants::MCU_TOG_ECU3BUS_TEST:
        case JigaTestConstants::MCU_TOG_ECU4BUS_TEST:
            if(header){
                strMessage = QString(CmdMessageConstants::CMD_HDR_MCU_INTERFACE) + " ";
            }
            strMessage += testMessage;
            mcu1InterModel->addTestMessage(boardId, strMessage);
            break;
        default:
            break;
        }

}

void BusinessController::sendAtCommand(int testId, int boardId, const QString &atCommand) {
    QString commPort = psController->getBoardCommPort(boardId);
    QString testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + CmdMessageConstants::MSG_SEND_AT_COMMAND;

    //1-Setting message
    addCmdTestMessage(testId,boardId,testMessage,false);

    //2- Sending Command
    psController->serialBoardWrite(boardId,atCommand,true);

    //3 - Setting message
    testMessage = commPort+CmdMessageConstants::MSG_SEPARATOR+atCommand;
    addCmdTestMessage(testId,boardId,testMessage,false);

}

bool BusinessController::acknowledgeAtCommand(int testId, int boardId)
{
    int timeout = (boardId == JigaTestConstants::MCU1_BOARD_ID) ?
                      JigaTestConstants::MCU_AT_COMMAND_TIMEOUT :
                      JigaTestConstants::ECU_AT_COMMAND_TIMEOUT;

    QString commPort = psController->getBoardCommPort(boardId);
    QString testMessage = commPort + ": " + CmdMessageConstants::MSG_READING_RECEIVED_MESSAGE;
    addCmdTestMessage(testId, boardId, testMessage, false);

    // Simulando um bloqueio sem interromper o processamento de eventos
    QEventLoop loop;
    QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
    loop.exec();

    QString recvStr = psController->serialBoardRead(boardId);
    testMessage = commPort + ": " + recvStr;
    addCmdTestMessage(testId, boardId, testMessage, false);

    switch(boardId){
    case JigaTestConstants::ECU1_BOARD_ID:
        return recvStr == AtCommandConstants::AT_ECU1_OK;

    case JigaTestConstants::ECU2_BOARD_ID:
        return recvStr == AtCommandConstants::AT_ECU2_OK;

    case JigaTestConstants::ECU3_BOARD_ID:
        return recvStr == AtCommandConstants::AT_ECU3_OK;

    case JigaTestConstants::ECU4_BOARD_ID:
        return recvStr == AtCommandConstants::AT_ECU4_OK;
    case JigaTestConstants::MCU1_BOARD_ID:
        return recvStr == AtCommandConstants::AT_MCU1_OK;

    }

    return false;

}

int BusinessController::getTestReportCode(const QString &recvStr) {
    bool ok;
    int codeInt = QStringView(recvStr).mid(9).toInt(&ok); // Extrai a substring a partir do índice 9 e tenta converter para int.

    if (!ok) {
        // Se a conversão falhar, retorna o código de erro.
        return EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE;
    }

    return codeInt; // Retorna o valor convertido se a conversão for bem-sucedida.
}




