#include "EcuFrameController.h"
#include <QDebug>

EcuFrameController::EcuFrameController(QObject *parent)
    : FrameController(parent) {
    setupModels();
}

EcuFrameController::~EcuFrameController() {
    // Clean-up code if necessary
}

void EcuFrameController::setupModels() {
    // Setup and initialize models, connect signals to slots for event handling
    connect(&timer, &QTimer::timeout, this, &EcuFrameController::handleTimeout);
}

// CONSERTAR
void EcuFrameController::executeTest(int test_id, int board_id) {
    QString testMessage;
    bool testStarted;
    int boardLoaded = bsController->loadBoard(test_id, board_id);

    if (!bsController) {
        qWarning() << "Business controller not set.";
        return;
    }

    resetTestModel(test_id);

    testMessage = (board_id == JigaTestConstants::MCU1_BOARD_ID) ? " iniciada!" : " iniciado!";
    addHeaderTestMessage(test_id, board_id, testMessage);

    if (boardLoaded != ErrorCodeInterface::SUCCESS) {
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
        bsController->addCmdTestMessage(test_id,board_id,testMessage,true);
        return;
    }

    testStarted = bsController->startIndividualBoardTest(test_id, board_id);
    if (!testStarted) {
        testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(board_id);
        bsController->addCmdTestMessage(test_id,board_id,testMessage,true);
        commTestModel->setTestResult(board_id, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
    } else {
        waitReportTestTimeOut(test_id, 0,board_id);
    }

    addHeaderTestMessage(test_id, board_id, " finalizado!");


}

void EcuFrameController::executeTest(int test_id)
{
    int numberOfBoards;
    QString testMessage;

    if (!bsController) {
        qWarning() << "Business controller not set.";
        return;
    }

    //1 - Resetting conditions
    resetTestModel(test_id);

    //2 - Adding message to start the test
    testMessage = " iniciado!";
    addHeaderTestMessage(test_id,JigaTestConstants::ALL_BOARDS_ID,testMessage);

    //3 - Load board information
    numberOfBoards = bsController->loadAllBoards(test_id);
    if(numberOfBoards==0){
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
        bsController->addCmdTestMessage(test_id,JigaTestConstants::ALL_BOARDS_ID,testMessage,true);
        return;
    }

    //4 - Start collective board test
    switch (test_id) {
    case JigaTestConstants::ANALOG_OUTPUT_TEST:
        executeAnalogOutputTest();
        break;
    case JigaTestConstants::LIN_NETWORK_TEST:
        executeLinNetworkTest();
        break;
    case JigaTestConstants::CAN_INIT_TEST:
        executeCanInitTest();
        break;
    case JigaTestConstants::CAN1_NETWORK_TEST:
        executeCan1NetworkTest();
        break;
    case JigaTestConstants::CAN2_NETWORK_TEST:
        executeCan2NetworkTest();
        break;
    case JigaTestConstants::COMMUNICATION_TEST:
        executeCommunicationTest();
        break;
    case JigaTestConstants::DIGITAL_INPUT_TEST:
        executeDigitalInputTest();
        break;
    case JigaTestConstants::ANALOG_INPUT_TEST:
        executeAnalogInputTest();
        break;
    case JigaTestConstants::LOOPBACK_CAN_TEST:
        executeLoopbackCanTest();
        break;
    default:
        qDebug() << "Unknown test ID:" << test_id;
        break;
    }
    addHeaderTestMessage(test_id,JigaTestConstants::ALL_BOARDS_ID," finalizado!");
}

void EcuFrameController::executeTestReport(int test_id)
{
    if (!rpController) {
        qWarning() << "Report controller not set.";
        return;
    }

    switch (test_id) {
    case JigaTestConstants::COMMUNICATION_TEST:
        rpController->showCommTestReport();
        break;
    default:
        qWarning() << "Unknown test ID for report:" << test_id;
        break;
    }
}

void EcuFrameController::executeCommunicationTest()
{
    QString testMessage;
    bool testStarted;

    auto testBoard = [&](int boardID) {
        testStarted = bsController->startIndividualBoardTest(JigaTestConstants::COMMUNICATION_TEST,boardID);
        if (!testStarted) {
            commTestModel->setTestResult(boardID, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
            testMessage = QString(CmdMessageConstants::CMD_ERROR_TEST_EXECUTION) + " (" + commTestModel->getBoardDescription(boardID) + ")";
            bsController->addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, boardID, testMessage, true);
        } else {
            commTestModel->setTestResult(boardID,JigaTestConstants::SUCCESS_EXECUTE_TEST);
            testMessage = QString(CmdMessageConstants::CMD_SUCCESS_TEST_EXECUTION) + " (" + commTestModel->getBoardDescription(boardID) + ")";
            bsController->addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, boardID, testMessage, true);
        }
    };

    // Iterating through each board
    testBoard(JigaTestConstants::ECU1_BOARD_ID);
    testBoard(JigaTestConstants::ECU2_BOARD_ID);
    testBoard(JigaTestConstants::ECU3_BOARD_ID);
    testBoard(JigaTestConstants::ECU4_BOARD_ID);
    testBoard(JigaTestConstants::MCU1_BOARD_ID);
}

void EcuFrameController::executeCan1NetworkTest() {
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            c1NetworkModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
        } else {
            bsController->addCmdTestMessage(testId, boardId, CmdMessageConstants::MSG_SUCCESS_START_TEST, true);
        }
        return testStarted;
    };

    // Trying to set CANBUS1 FOR ECUs
    if (!handleTest(JigaTestConstants::MCU_SEL_CANBUS1_TEST, JigaTestConstants::MCU1_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU1_BOARD_ID)) return;

    bsController->addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::CAN_NETWORK_TEST_OFFSET, JigaTestConstants::ALL_BOARDS_ID);
}


void EcuFrameController::executeCan2NetworkTest()
{
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            c2NetworkModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
        } else {
            bsController->addCmdTestMessage(testId, boardId, CmdMessageConstants::MSG_SUCCESS_START_TEST, true);
        }
        return testStarted;
    };

    // Trying to set CANBUS2 FOR ECUs
    if (!handleTest(JigaTestConstants::MCU_SEL_CANBUS2_TEST, JigaTestConstants::MCU1_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU1_BOARD_ID)) return;

    bsController->addCmdTestMessage(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::CAN_NETWORK_TEST_OFFSET, JigaTestConstants::ALL_BOARDS_ID);
}

void EcuFrameController::executeDigitalInputTest() {
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            diInputModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
        } else {
            testMessage = QString(CmdMessageConstants::MSG_SUCCESS_START_TEST) + " (" + commTestModel->getBoardDescription(boardId) + ")";
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
        }
        return testStarted;
    };

    if (!handleTest(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU1_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU4_BOARD_ID)) return;

    bsController->addCmdTestMessage(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_DIGITAL_TEST, true);
    waitReportTestTimeOut(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::DIGITAL_INPUT_TEST_OFFSET,JigaTestConstants::ALL_BOARDS_ID);
}

void EcuFrameController::executeAnalogOutputTest()
{
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            anOutputModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
            return false;
        } else {
            bsController->addCmdTestMessage(testId, boardId, CmdMessageConstants::MSG_SUCCESS_START_TEST, true);
            return true;
        }
    };

    if (!handleTest(JigaTestConstants::ANALOG_OUTPUT_TEST, JigaTestConstants::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::ANALOG_OUTPUT_TEST, JigaTestConstants::ECU1_BOARD_ID)) return;

    bsController->addCmdTestMessage(JigaTestConstants::ANALOG_OUTPUT_TEST, JigaTestConstants::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestConstants::ANALOG_OUTPUT_TEST, JigaTestConstants::ANALOG_OUTPUT_TEST_OFFSET,JigaTestConstants::ALL_BOARDS_ID);
}

void EcuFrameController::executeLinNetworkTest()
{
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            lnNetworkModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
            return false;
        } else {
            bsController->addCmdTestMessage(testId, boardId, CmdMessageConstants::MSG_SUCCESS_START_TEST, true);
            return true;
        }
    };

    // Testing for ECU3
    if (!handleTest(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID)) return;

    // Testing for ECU4
    if (!handleTest(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID)) return;

    bsController->addCmdTestMessage(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::LIN_NETWORK_TEST_OFFSET,JigaTestConstants::ALL_BOARDS_ID);
}

void EcuFrameController::executeCanInitTest()
{


    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::CMD_ERROR_TEST_EXECUTION) + " (" + canInitModel->getBoardDescription(boardId) + ")";
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            canInitModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
            return false;
        } else {
            testMessage = QString(CmdMessageConstants::CMD_SUCCESS_TEST_EXECUTION) + " (" + canInitModel->getBoardDescription(boardId) + ")";
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            return true;
        }
    };

    // Execute test for ECU1 to ECU4
    if (!handleTest(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU1_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU4_BOARD_ID)) return;
}

void EcuFrameController::executeLoopbackCanTest()
{

    // Lambda to simplify repetitive testing and message logging
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            lbNetworkModel->setTestResult(boardId, JigaTestConstants::LOOPBACK_CAN_TEST);
            return false;
        } else {
            bsController->addCmdTestMessage(testId, boardId, CmdMessageConstants::MSG_SUCCESS_START_TEST, true);
            return true;
        }
    };

    // Execute loopback test for each ECU
    if (!handleTest(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU1_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU4_BOARD_ID)) return;

    // Message indicating waiting for results after all tests initiated
    bsController->addCmdTestMessage(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::CAN_NETWORK_TEST_OFFSET,JigaTestConstants::ALL_BOARDS_ID);
}

void EcuFrameController::executeAnalogInputTest()
{
    // A lambda function to handle repetitive test execution and messaging logic
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            // Assuming diInputModel can set test results if needed
            diInputModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
        } else {
            testMessage = QString(CmdMessageConstants::MSG_SUCCESS_START_TEST) + " (" + commTestModel->getBoardDescription(boardId) + ")";
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
        }
        return testStarted;
    };

    // Execute test for all designated ECUs
    if (!handleTest(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU1_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU4_BOARD_ID)) return;

    // After all tests have started, send a message indicating that the system is waiting for results
    bsController->addCmdTestMessage(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_ANALOG_TEST, true);

    // Implement waiting for the test report based on a timeout specified in constants
    waitReportTestTimeOut(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ANALOG_INPUT_TEST_OFFSET,JigaTestConstants::ALL_BOARDS_ID);
}




void EcuFrameController::executeFirmwareUpload(int board_id) {
    int retVal;
    QString testMessage;

    // 1 - Resetting conditions
    resetTestModel(JigaTestConstants::FIRMWARE_UPLOAD);

    // 2 - Adding message to start the test
    testMessage = " iniciado!";
    addHeaderTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage);

    // 3 - Load the serial communication ports
    retVal = bsController->loadAllSerialCommPorts();
    if (retVal <= 0) {
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
                      bsController->addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, board_id, testMessage, true);
        return;
    }

    // Checking board id
    if (board_id == JigaTestConstants::ALL_BOARDS_ID) {
        // Iterating over all board IDs
        const QList<int> boardIds = {JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::ECU4_BOARD_ID};
        for (int id : boardIds) {
            //Sending External Reset TimeOut
            bsController->startIndividualBoardTest(JigaTestConstants::MCU_RST_ATT_TEST, JigaTestConstants::MCU1_BOARD_ID);
            //Start firmware upload
            bsController->uploadFirmware(id);
        }
    } else {
        //Sending External Reset TimeOut
        bsController->startIndividualBoardTest(JigaTestConstants::MCU_RST_ATT_TEST, JigaTestConstants::MCU1_BOARD_ID);
         //Start firmware upload
        bsController->uploadFirmware(board_id);
    }

    // Adding message to finish the test
    addHeaderTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, board_id, " finalizado!");
}

void EcuFrameController::executeFirmwareUpload(int port_id, const QString &pathToHexFile)
{
    int retVal;
    QString testMessage;

    // 1 - Resetting conditions
    resetTestModel(JigaTestConstants::FIRMWARE_UPLOAD);

    // 2 - Adding message to start the test
    testMessage = "iniciada!";
    addHeaderTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage);

    // 3 - Load the serial communication ports
    retVal = bsController->loadAllSerialCommPorts();
    if (retVal <= 0) {
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
                      bsController->addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, true);
        return;
    }

    // 4 - Sending External Reset TimeOut
    bsController->startIndividualBoardTest(JigaTestConstants::MCU_RST_ATT_TEST, JigaTestConstants::MCU1_BOARD_ID);

    // 5 - Start firmware upload
    if (!bsController->uploadFirmware(port_id, pathToHexFile)) {
        testMessage = "Falha ao carregar o firmware";
        bsController->addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, true);
        return;
    }

    // 6 - Adding message to finish the test
    addHeaderTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, "finalizada!");
}

void EcuFrameController::setEcuBusinessController(EcuBusinessInterface bsInterface)
{
    this->bsController = &bsInterface;
}

SerialCommPort *EcuFrameController::getSerialCommPortsInfo()
{
    return bsController->getSerialCommPortsInfo();
}

void EcuFrameController::handleTimeout() {
    qDebug() << "Test timeout occurred";
    // Handle test timeout
}

void EcuFrameController::waitReportTestTimeOut(int test_id, int offset, int board_id) {
    // Ensuring 'board_id' is captured by value safely for use after the function exits
    QTimer::singleShot(offset * 1000, this, [this, test_id, board_id]() {
        emit testFinished(test_id, board_id, "Test timeout occurred.");
    });
}


