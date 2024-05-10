#include "RepBusinessController.h"
#include <QDebug>
#include <QThread>

RepBusinessController::RepBusinessController(QObject *parent)
    : BusinessController(parent) {
    psController = PersistenceController::getInstance();
}

void RepBusinessController::startTestResultMonitor(int testId, int boardId) {
    TimeOutMonitor *timeOutThread = new TimeOutMonitor(this);  // Assegura gerenciamento de memória adequado
    timeOutThread->setBoardID(boardId);
    timeOutThread->setTestID(testId);
    timeOutThread->addTimeOutListener(this);

    switch(testId) {
    case JigaTestConstants::DIGITAL_INPUT_TEST:
        timeOutThread->setTimeOut(JigaTestConstants::DIGITAL_INPUT_TEST_TIMEOUT);
        break;
    case JigaTestConstants::ANALOG_INPUT_TEST:
        timeOutThread->setTimeOut(JigaTestConstants::ANALOG_INPUT_TEST_TIMEOUT);
        break;
    case JigaTestConstants::ANALOG_OUTPUT_TEST:
        timeOutThread->setTimeOut(JigaTestConstants::ANALOG_OUTPUT_TEST_TIMEOUT);
        break;
    case JigaTestConstants::LOOPBACK_CAN_TEST:
    case JigaTestConstants::CAN1_NETWORK_TEST:
    case JigaTestConstants::CAN2_NETWORK_TEST:
        timeOutThread->setTimeOut(JigaTestConstants::CAN_NETWORK_TEST_TIMEOUT);
        break;
    case JigaTestConstants::LIN_NETWORK_TEST:
        timeOutThread->setTimeOut(JigaTestConstants::LIN_NETWORK_TEST_TIMEOUT);
        break;
    case JigaTestConstants::MCU_GET_CANBUS_TEST:
        timeOutThread->setTimeOut(JigaTestConstants::MCU_CANBUS_TEST_TIMEOUT);
        break;
    default:
        qWarning() << "Test ID not recognized";
        delete timeOutThread;  // Remove a instância se não for usada
        return;
    }

    timeOutThread->start();
}

void RepBusinessController::getTestResult(int testId, int boardId) {
    QString recvStr;
    bool portOpened = psController->openConnection(boardId, 115200);

    if (portOpened) {
        recvStr = psController->serialBoardRead(boardId);
        QString commPort = psController->getBoardCommPort(boardId);
        QString testMessage = commPort + ": " + recvStr;
        addCmdTestMessage(testId, boardId, testMessage, false);
    }

    switch (testId) {
    case JigaTestConstants::DIGITAL_INPUT_TEST:
        //checkDigitalInputReport(boardId, recvStr);
        break;
    case JigaTestConstants::ANALOG_INPUT_TEST:
        //checkAnalogInputReport(boardId, recvStr);
        break;
    case JigaTestConstants::ANALOG_OUTPUT_TEST:
        //checkAnalogOutputReport(boardId, recvStr);
        break;
    case JigaTestConstants::LOOPBACK_CAN_TEST:
        //checkLBCanNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::CAN1_NETWORK_TEST:
        //checkC1CanNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::CAN2_NETWORK_TEST:
        //checkC2CanNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::LIN_NETWORK_TEST:
        //checkLinNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::MCU_GET_CANBUS_TEST:
        //checkMcuGetCanBusReport(recvStr);
        break;
    default:
        qDebug() << "Unknown test ID:" << testId;
        break;
    }

    psController->closeBoardConnection(boardId);
}

