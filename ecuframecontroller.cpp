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

    resetTestModel(test_id);

    testMessage = (board_id == JigaTestConstants::MCU1_BOARD_ID) ? " iniciada!" : " iniciado!";
    addHeaderTestMessage(test_id, board_id, testMessage);

    if (boardLoaded != ErrorCodeInterface::SUCCESS) {
        testMessage = "Unavailable serial port";
        emit errorOccurred(test_id, board_id, testMessage);
        return;
    }

    testStarted = bsController->startIndividualBoardTest(test_id, board_id);
    if (!testStarted) {
        testMessage = "Error to run test " + commTestModel->getBoardDescription(board_id);
        emit errorOccurred(test_id, board_id, testMessage);
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

void EcuFrameController::executeCan1NetworkTest()
{

}

void EcuFrameController::executeCan2NetworkTest()
{

}

void EcuFrameController::executeDigitalInputTest()
{

}

void EcuFrameController::executeAnalogOutputTest()
{

}

void EcuFrameController::executeLinNetworkTest()
{

}

void EcuFrameController::executeCanInitTest()
{

}

void EcuFrameController::executeLoopbackCanTest()
{

}

void EcuFrameController::executeAnalogInputTest()
{

}



void EcuFrameController::executeFirmwareUpload(int board_id) {
    qDebug() << "Uploading firmware for board:" << board_id;
    emit testStarted(JigaTestConstants::FIRMWARE_UPLOAD, board_id, "Firmware upload started");
    // Example firmware upload process
}

void EcuFrameController::setEcuBusinessController(EcuBusinessInterface bsInterface)
{
    this->bsController = &bsInterface;
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


void EcuFrameController::resetTestModel(int test_id) {
    // Reset the test model based on the test_id
    qDebug() << "Resetting test model for test ID:" << test_id;
}

void EcuFrameController::addHeaderTestMessage(int test_id, int board_id, const QString &message) {
    emit testStarted(test_id, board_id, message);
}
