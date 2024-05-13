#include "EcuBusinessController.h"
#include <QThread>
#include <QDebug>

EcuBusinessController::EcuBusinessController(QObject *parent)
    : BusinessController(parent){

}


bool EcuBusinessController::startIndividualBoardTest(int testId, int boardId) {
    QString testMessage;
    QString commPort;

    for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
        if (psController->openBoardConnection(boardId)) {
            commPort = psController->getBoardCommPort(boardId);
            testMessage = commPort + ":" + CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT;
            addCmdTestMessage(testId, boardId, testMessage, false);

            if (startTestExecution(testId, boardId)) {

                switch (testId) {
                case JigaTestConstants::CAN_INIT_TEST:
                case JigaTestConstants::MCU_RST_ACT_TEST:
                case JigaTestConstants::MCU_RST_DAC_TEST:
                case JigaTestConstants::MCU_RST_ATT_TEST:
                case JigaTestConstants::COMMUNICATION_TEST:
                case JigaTestConstants::MCU_IDENT_PORT_TEST:
                case JigaTestConstants::MCU_SEL_CANBUS1_TEST:
                case JigaTestConstants::MCU_SEL_CANBUS2_TEST:
                case JigaTestConstants::MCU_TOG_ECU3BUS_TEST:
                case JigaTestConstants::MCU_TOG_ECU4BUS_TEST:
                    testMessage = commPort + ":" + CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT;
                    addCmdTestMessage(testId, boardId, testMessage, false);
                    psController->closeBoardConnection(boardId);

                    switch (testId) {
                    case JigaTestConstants::MCU_RST_ATT_TEST :
                        mcu1InterModel->setIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID,JigaTestConstants::MCU_RST_ATT_ITEST,JigaTestConstants::SUCCESS_EXECUTE_TEST);
                        break;

                    case JigaTestConstants::MCU_SEL_CANBUS1_TEST:
                        Ecu3Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_1);
                        Ecu4Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_1);
                        mcu1InterModel->setIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID,JigaTestConstants::MCU_SEL_CANBUS1_ITEST,JigaTestConstants::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestConstants::MCU_SEL_CANBUS2_TEST:
                        Ecu3Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_2);
                        Ecu4Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_2);
                        mcu1InterModel->setIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID,JigaTestConstants::MCU_SEL_CANBUS2_ITEST,JigaTestConstants::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestConstants::MCU_TOG_ECU3BUS_TEST:
                        Ecu3Board::getInstance()->toggleCanBus();
                        mcu1InterModel->setIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID,JigaTestConstants::MCU_TOG_ECU3BUS_ITEST,JigaTestConstants::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestConstants::MCU_TOG_ECU4BUS_TEST:
                        Ecu4Board::getInstance()->toggleCanBus();
                        mcu1InterModel->setIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID,JigaTestConstants::MCU_TOG_ECU4BUS_ITEST,JigaTestConstants::SUCCESS_EXECUTE_TEST);
                        break;
                    default:
                        break;
                    }
                    break;

                default:
                    repController->startTestResultMonitor(testId,boardId);
                }
                return true;

            } else {
                testMessage = commPort + ": " + CmdMessageConstants::MSG_ERR_START_TEST ;
                addCmdTestMessage(testId, boardId, testMessage, false);
            }
            psController->closeBoardConnection(boardId);
        } else {
            testMessage = CmdMessageConstants::MSG_ERROR_TO_OPEN_PORT;
            addCmdTestMessage(testId, boardId, testMessage, true);

            testMessage = QString("%1 (%2)").arg(CmdMessageConstants::MSG_TRY_CONNECTION_AGAIN).arg(i + 1);
            addCmdTestMessage(testId, boardId, testMessage, true);
            QThread::sleep(1000);  // Atraso sincronizado, não recomendado na UI thread
        }
    }

    return false;
}

int EcuBusinessController::loadBoard(int testId, int boardId) {
    // Example: Implement similarly to Java code
    return 0;
}

int EcuBusinessController::uploadFirmware(int boardId) {
    // Example: Implement similarly to Java code
    return 0;
}


bool EcuBusinessController::startTestExecution(int testId, int boardId) {
    QString commPort = psController->getBoardCommPort(boardId);
    QString testMessage = commPort + ": Sending AT command";
    addCmdTestMessage(testId, boardId, testMessage, false);
    // Example: Add logic to send commands to board
    return true; // Simulated result
}
