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
        checkDigitalInputReport(boardId, recvStr);
        break;
    case JigaTestConstants::ANALOG_INPUT_TEST:
        checkAnalogInputReport(boardId, recvStr);
        break;
    case JigaTestConstants::ANALOG_OUTPUT_TEST:
        checkAnalogOutputReport(boardId, recvStr);
        break;
    case JigaTestConstants::LOOPBACK_CAN_TEST:
        checkLBCanNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::CAN1_NETWORK_TEST:
        checkC1CanNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::CAN2_NETWORK_TEST:
        checkC2CanNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::LIN_NETWORK_TEST:
        checkLinNetworkReport(boardId, recvStr);
        break;
    case JigaTestConstants::MCU_GET_CANBUS_TEST:
        checkMcuGetCanBusReport(recvStr);
        break;
    default:
        qDebug() << "Unknown test ID:" << testId;
        break;
    }

    psController->closeBoardConnection(boardId);
}

void RepBusinessController::checkDigitalInputReport(int boardId, const QString &recvStr)
{
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if(code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE){
        return;
    }

    //Checking code number
    testResult = UtilsConversion::parseBinary(code);

    for (int i = 0; i < testResult.size(); i++) {
        if(testResult[i] == 1){
            testMessage = boardDesc + "->DIN#" + QString::number(i+1) + ": lida com sucesso!";
            qDebug() << testMessage;
            switch (boardId) {
            case JigaTestConstants::ECU1_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::DIN1_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU2_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::DIN2_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU3_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::DIN3_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU4_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU4_BOARD_ID, JigaTestConstants::DIN4_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            default:
                qDebug() << "Unknown board ID:" << boardId;
                break;
            }
        } else {
            testMessage = boardDesc + "->DIN#" + QString::number(i+1) + ": erro de leitura!";
            qDebug() << testMessage;
            switch (boardId) {
            case JigaTestConstants::ECU1_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::DIN1_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU2_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::DIN2_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU3_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::DIN3_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU4_BOARD_ID:
                diInputModel->setIndividualTestResult(JigaTestConstants::ECU4_BOARD_ID, JigaTestConstants::DIN4_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            default:
                qDebug() << "Unknown board ID:" << boardId;
                break;
            }
        }
    }

    addCmdTestMessage(JigaTestConstants::DIGITAL_INPUT_TEST,boardId,testMessage,true);

}

void RepBusinessController::checkAnalogInputReport(int boardId, const QString &recvStr)
{
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        return;
    }

    // Checking code number
    testResult = UtilsConversion::parseBinary(code);

    for (int i = 0; i < testResult.size(); i++) {
        if (testResult[i] == 1) {
            testMessage = boardDesc + "->AIN#" + QString::number(i+1) + ": lida com sucesso!";
            qDebug() << testMessage;
            switch (boardId) {
            case JigaTestConstants::ECU1_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::AIN1_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU2_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::AIN2_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU3_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::AIN3_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU4_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU4_BOARD_ID, JigaTestConstants::AIN4_INPUT_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
                break;
            default:
                qDebug() << "Unknown board ID:" << boardId;
                break;
            }
        } else {
            testMessage = boardDesc + "->AIN#" + QString::number(i+1) + ": erro de leitura!";
            qDebug() << testMessage;
            switch (boardId) {
            case JigaTestConstants::ECU1_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::AIN1_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU2_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::AIN2_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU3_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::AIN3_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            case JigaTestConstants::ECU4_BOARD_ID:
                anInputModel->setIndividualTestResult(JigaTestConstants::ECU4_BOARD_ID, JigaTestConstants::AIN4_INPUT_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
                break;
            default:
                qDebug() << "Unknown board ID:" << boardId;
                break;
            }
        }
    }

    addCmdTestMessage(JigaTestConstants::DIGITAL_INPUT_TEST,boardId, testMessage, true);
}

void RepBusinessController::checkAnalogOutputReport(int boardId, const QString &recvStr)
{
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    // Checking code number
    testResult = UtilsConversion::parseBinary(code);

    if (testResult[0] == 1) {
        testMessage = boardDesc + "->AOUT: lida com sucesso!";
        //qDebug() << testMessage;
        if (boardId == JigaTestConstants::ECU1_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::AOUT1_LDR_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
        } else if (boardId == JigaTestConstants::ECU2_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::AOUT2_LOOP_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
        }
    } else {
        testMessage = boardDesc + "->AOUT: erro de leitura!";
        //qDebug() << testMessage;
        if (boardId == JigaTestConstants::ECU1_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::AOUT1_LDR_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
        } else if (boardId == JigaTestConstants::ECU2_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::AOUT2_LOOP_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
        }
    }

    addCmdTestMessage(JigaTestConstants::ANALOG_OUTPUT_TEST, boardId, testMessage, true);
}

void RepBusinessController::checkLBCanNetworkReport(int boardId, const QString &recvStr)
{
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    // Checking code number
    testResult = UtilsConversion::parseBinary(code);

    if (boardId == JigaTestConstants::ECU2_BOARD_ID) {
        if (testResult[1] == 1) {
            testMessage = boardDesc + "->CAN2 (Loopback): Teste executado com sucesso!";
            anOutputModel->setIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::AOUT1_LDR_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
        } else {
            testMessage = boardDesc + "->CAN2 (Loopback): Erro de execução do teste!";
        }
        addCmdTestMessage(JigaTestConstants::LOOPBACK_CAN_TEST, boardId, testMessage, true);
    }

    if (testResult[0] == 1) {
        testMessage = boardDesc + "->CAN1 (Loopback): Teste executado com sucesso!";
    } else {
        testMessage = boardDesc + "->CAN1 (Loopback): Erro de execução do teste!";
    }
    addCmdTestMessage(JigaTestConstants::LOOPBACK_CAN_TEST, boardId, testMessage, true);

}



void RepBusinessController::checkC1CanNetworkReport(int boardId, const QString &recvStr)
{
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    // Checking code number
    testResult = UtilsConversion::parseBinary(code);

    switch (boardId) {
    case JigaTestConstants::ECU1_BOARD_ID:
        for (int i = 0; i < testResult.size() - 1; i++) {
            if (testResult[i] == 1) {
                testMessage = boardDesc + "->CAN1: recebida mensagem de ECU" + QString::number(i + 2);
            } else {
                testMessage = boardDesc + "->CAN1: erro de mensagem de ECU" + QString::number(i + 2);
            }
            addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
        break;

    case JigaTestConstants::ECU2_BOARD_ID: {
        int offset = 1;
        for (int i = 0; i < testResult.size() - 1; i++) {
            if (testResult[i] == 1) {
                testMessage = boardDesc + "->CAN1: recebida mensagem de ECU" + QString::number(i + offset);
            } else {
                testMessage = boardDesc + "->CAN1: erro de mensagem de ECU" + QString::number(i + offset);
            }
            if (i <= 0) {
                offset = 2;
            }
            addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
    } break;

    case JigaTestConstants::ECU3_BOARD_ID: {
        int offset = 1;
        for (int i = 0; i < testResult.size() - 1; i++) {
            if (testResult[i] == 1) {
                testMessage = boardDesc + "->CAN1: recebida mensagem de ECU" + QString::number(i + offset);
            } else {
                testMessage = boardDesc + "->CAN1: erro de mensagem de ECU" + QString::number(i + offset);
            }
            if (i >= 1) {
                offset = 2;
            }
            addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
    } break;

    case JigaTestConstants::ECU4_BOARD_ID:
        for (int i = 0; i < testResult.size() - 1; i++) {
            if (testResult[i] == 1) {
                testMessage = boardDesc + "->CAN1: recebida mensagem de ECU" + QString::number(i + 1);
            } else {
                testMessage = boardDesc + "->CAN1: erro de mensagem de ECU" + QString::number(i + 1);
            }
            addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
        break;

    default:
        qDebug() << "Unknown board ID:" << boardId;
        break;
    }
}

void RepBusinessController::checkC2CanNetworkReport(int boardId, const QString &recvStr) {
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    // Verificando código numérico
    testResult = UtilsConversion::parseBinary(code);

    switch (boardId) {
    case JigaTestConstants::ECU2_BOARD_ID: {
        for (int i = 0; i < (testResult.size() - 2); i++) {
            if (testResult[i] == 1) {
                testMessage = boardDesc + "->CAN2: recebida mensagem de ECU" + QString::number(i + 3);
            } else {
                testMessage = boardDesc + "->CAN2: erro de mensagem de ECU" + QString::number(i + 3);
            }
            addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
    }
    break;

    case JigaTestConstants::ECU3_BOARD_ID: {
        int offset = 2;
        for (int i = 0; i < (testResult.size() - 2); i++) {
            if (testResult[i] == 1) {
                testMessage = boardDesc + "->CAN1: recebida mensagem de ECU" + QString::number(i + offset);
            } else {
                testMessage = boardDesc + "->CAN1: erro de mensagem de ECU" + QString::number(i + offset);
            }
            if (i <= 0) {
                offset = 3;
            }
            addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
    }
    break;

    case JigaTestConstants::ECU4_BOARD_ID: {
        for (int i = 0; i < (testResult.size() - 2); i++) {
            if (testResult[i] == 1) {
                testMessage = boardDesc + "->CAN1: recebida mensagem de ECU" + QString::number(i + 2);
            } else {
                testMessage = boardDesc + "->CAN1: erro de mensagem de ECU" + QString::number(i + 2);
            }
            addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
    }
    break;

    default:
        qDebug() << "Unknown board ID:" << boardId;
    break;
    }
}

void RepBusinessController::checkLinNetworkReport(int boardId, const QString &recvStr) {
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
    qDebug() << "Error to read report code!";
    return;
    }

    // Verificando código numérico
    testResult = UtilsConversion::parseBinary(code);

    int lnSize = lnNetworkModel->getSize(); // Assegure-se que lnNetworkModel tem um método getSize()
    for (int i = 0; i < (lnSize - 2); i++) {
    if (testResult[i] == 1) {
            testMessage = boardDesc + "->LIN: Mensagem lida com sucesso!";
            if (boardId == JigaTestConstants::ECU3_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::LIN1_ECU3_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
            } else if (boardId == JigaTestConstants::ECU4_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestConstants::ECU4_BOARD_ID, JigaTestConstants::LIN1_ECU4_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
            }
    } else {
            testMessage = boardDesc + "->LIN: Erro na leitura da mensagem!";
            if (boardId == JigaTestConstants::ECU3_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::LIN1_ECU3_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
            } else if (boardId == JigaTestConstants::ECU4_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestConstants::ECU4_BOARD_ID, JigaTestConstants::LIN1_ECU4_ITEST, JigaTestConstants::ERROR_TO_EXECUTE_TEST);
            }
    }
    addCmdTestMessage(JigaTestConstants::LIN_NETWORK_TEST, boardId, testMessage, true);
    }
}

void RepBusinessController::showCommTestReport() {
    int testResult;
    QString reportMessage;

    // Verificando Teste de Comunicação - ECU1
    testResult = commTestModel->getIndividualTestResult(JigaTestConstants::ECU1_BOARD_ID, JigaTestConstants::COMM_ECU1_ITEST);
    if (testResult == JigaTestConstants::ERROR_TO_EXECUTE_TEST) {
    reportMessage = psController->getReportProperty("com.ecu1.err");
    } else {
    reportMessage = QString("%1 com a ECU1 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU1_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - ECU2
    testResult = commTestModel->getIndividualTestResult(JigaTestConstants::ECU2_BOARD_ID, JigaTestConstants::COMM_ECU2_ITEST);
    if (testResult == JigaTestConstants::ERROR_TO_EXECUTE_TEST) {
    reportMessage = psController->getReportProperty("com.ecu2.err");
    } else {
    reportMessage = QString("%1 com a ECU2 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU2_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - ECU3
    testResult = commTestModel->getIndividualTestResult(JigaTestConstants::ECU3_BOARD_ID, JigaTestConstants::COMM_ECU3_ITEST);
    if (testResult == JigaTestConstants::ERROR_TO_EXECUTE_TEST) {
    reportMessage = psController->getReportProperty("com.ecu3.err");
    } else {
    reportMessage = QString("%1 com a ECU3 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU3_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - ECU4
    testResult = commTestModel->getIndividualTestResult(JigaTestConstants::ECU4_BOARD_ID, JigaTestConstants::COMM_ECU4_ITEST);
    if (testResult == JigaTestConstants::ERROR_TO_EXECUTE_TEST) {
    reportMessage = psController->getReportProperty("com.ecu4.err");
    } else {
    reportMessage = QString("%1 com a ECU4 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU4_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - PROG
    testResult = commTestModel->getIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID, JigaTestConstants::COMM_PROG_ITEST);
    if (testResult == JigaTestConstants::ERROR_TO_EXECUTE_TEST) {
    reportMessage = psController->getReportProperty("com.prog.err");
    } else {
    reportMessage = QString("%1 com o PROG realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::MCU1_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - MCU1
    testResult = commTestModel->getIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID, JigaTestConstants::COMM_MCU1_ITEST);
    if (testResult == JigaTestConstants::ERROR_TO_EXECUTE_TEST) {
    reportMessage = psController->getReportProperty("com.mcu1.err");
    } else {
    reportMessage = QString("%1 com o PROG realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    addCmdTestMessage(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::MCU1_BOARD_ID, reportMessage, true);
}

void RepBusinessController::checkMcuGetCanBusReport(const QString &recvStr) {
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(JigaTestConstants::MCU1_BOARD_ID);
    QString testMessage;

    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
    qDebug() << "RepBusinessController: Board =" << boardDesc << "error to read report code!";
    qDebug() << "Serial output:" << recvStr;
    return;
    }

    // Verificação do código numérico
    testResult = UtilsConversion::parseBinary(code);

    // ECU3 - CANBUS1
    if (testResult[0] == 0) {
    testMessage = boardDesc + "-> ECU3 conectada no CANBUS1!";
    Ecu3Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_1);
    } else {
    testMessage = boardDesc + "-> ECU3 conectada no CANBUS2!";
    Ecu3Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_2);
    }
    addCmdTestMessage(JigaTestConstants::MCU_GET_CANBUS_TEST, JigaTestConstants::MCU1_BOARD_ID, testMessage, true);

    // ECU4 - CANBUS1 or CANBUS2
    if (testResult[1] == 0) {
    testMessage = boardDesc + "-> ECU4 conectada no CANBUS1!";
    Ecu4Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_1);
    } else {
    testMessage = boardDesc + "-> ECU4 conectada no CANBUS2!";
    Ecu4Board::getInstance()->setCanbus(JigaTestConstants::ECU_CANBUS_2);
    }
    addCmdTestMessage(JigaTestConstants::MCU_GET_CANBUS_TEST, JigaTestConstants::MCU1_BOARD_ID, testMessage, true);
    mcu1InterModel->setIndividualTestResult(JigaTestConstants::MCU1_BOARD_ID, JigaTestConstants::MCU_GET_CANBUS_ITEST, JigaTestConstants::SUCCESS_EXECUTE_TEST);
}
