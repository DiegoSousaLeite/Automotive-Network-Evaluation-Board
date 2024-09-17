#include "RepBusinessController.h"
#include <QDebug>
#include <QThread>

RepBusinessController::RepBusinessController(QObject *parent)
    : BusinessController(parent) {
    // Inicializa o controlador de persistência
    psController = PersistenceController::getInstance();
}

// Define as propriedades do relatório usando um mapa de strings
void RepBusinessController::setReportProperty(const QMap<QString, QString> &propFile)
{
    reportProperties = propFile;
}

// Obtém uma propriedade específica do relatório com base na chave fornecida
QString RepBusinessController::getReportProperty(const QString &key) const
{
    return reportProperties.value(key);
}

// Inicia a monitoração do resultado do teste, configurando o tempo limite com base no tipo de teste
void RepBusinessController::startTestResultMonitor(int testId, int boardId) {
    TimeOutMonitor *timeOutThread = new TimeOutMonitor(this);  // Assegura gerenciamento de memória adequado
    timeOutThread->setBoardID(boardId);
    timeOutThread->setTestID(testId);
    timeOutThread->addTimeOutListener(this);

    // Configura o tempo limite com base no tipo de teste
    switch(testId) {
    case JigaTestInterface::DIGITAL_INPUT_TEST:
        timeOutThread->setTimeOut(JigaTestInterface::DIGITAL_INPUT_TEST_TIMEOUT);
        break;
    case JigaTestInterface::ANALOG_INPUT_TEST:
        timeOutThread->setTimeOut(JigaTestInterface::ANALOG_INPUT_TEST_TIMEOUT);
        break;
    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        timeOutThread->setTimeOut(JigaTestInterface::ANALOG_OUTPUT_TEST_TIMEOUT);
        break;
    case JigaTestInterface::CAN_LOOPBACK_TEST:
    case JigaTestInterface::CAN1_NETWORK_TEST:
    case JigaTestInterface::CAN2_NETWORK_TEST:
        timeOutThread->setTimeOut(JigaTestInterface::CAN_NETWORK_TEST_TIMEOUT);
        break;
    case JigaTestInterface::LIN_NETWORK_TEST:
        timeOutThread->setTimeOut(JigaTestInterface::LIN_NETWORK_TEST_TIMEOUT);
        break;
    case JigaTestInterface::MCU_GET_CANBUS_TEST:
        timeOutThread->setTimeOut(JigaTestInterface::MCU_CANBUS_TEST_TIMEOUT);
        break;
    default:
        qWarning() << "Test ID not recognized";
        delete timeOutThread;  // Remove a instância se não for usada
        return;
    }

    // Inicia a monitoração do tempo limite do teste
    timeOutThread->start();
}

// Obtém e verifica o resultado do teste com base no tipo de teste e ID da placa
void RepBusinessController::getTestResult(int testId, int boardId) {
    QString recvStr;
    bool portOpened = psController->openConnection(boardId, 115200);

    if (portOpened) {
        // Lê o resultado do teste da placa e adiciona uma mensagem de teste de comando
        recvStr = psController->serialBoardRead(boardId);
        QString commPort = psController->getBoardCommPort(boardId);
        QString testMessage = commPort + ": " + recvStr;
        addCmdTestMessage(testId, boardId, testMessage, false);
    }

    // Verifica o resultado do teste com base no tipo de teste
    switch (testId) {
    case JigaTestInterface::DIGITAL_INPUT_TEST:
        checkDigitalInputReport(boardId, recvStr);
        break;
    case JigaTestInterface::ANALOG_INPUT_TEST:
        checkAnalogInputReport(boardId, recvStr);
        break;
    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        checkAnalogOutputReport(boardId, recvStr);
        break;
    case JigaTestInterface::CAN_LOOPBACK_TEST:
        checkLBCanNetworkReport(boardId, recvStr);
        break;
    case JigaTestInterface::CAN1_NETWORK_TEST:
        checkC1CanNetworkReport(boardId, recvStr);
        break;
    case JigaTestInterface::CAN2_NETWORK_TEST:
        checkC2CanNetworkReport(boardId, recvStr);
        break;
    case JigaTestInterface::LIN_NETWORK_TEST:
        checkLinNetworkReport(boardId, recvStr);
        break;
    case JigaTestInterface::MCU_GET_CANBUS_TEST:
        checkMcuGetCanBusReport(recvStr);
        break;
    default:
        qDebug() << "Unknown test ID:" << testId;
        break;
    }

    // Fecha a conexão com a placa
    psController->closeBoardConnection(boardId);
}

// Verifica e processa o relatório de teste de entrada digital
void RepBusinessController::checkDigitalInputReport(int boardId, const QString &recvStr)
{
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);

    // Verifica se ocorreu um erro ao recuperar o código do relatório
    if (code ==  EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        return;
    }

    QVector<int> testResult = UtilsConversion::parseBinary(code);

    // Processa os resultados individuais do teste de entrada digital
    for (int i = 0; i < testResult.size(); ++i) {
        QString testMessage;
        if (testResult[i] == 1) {
            testMessage = boardDesc + "->DIN#" + QString::number(i + 1) + ": lida com sucesso!";
            // Atualiza o modelo de entrada digital com base no resultado do teste
            switch (boardId) {
            case JigaTestInterface::ECU1_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU2_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU3_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU4_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            }
        } else {
            testMessage = boardDesc + "->DIN#" + QString::number(i + 1) + ": erro de leitura!";
            // Atualiza o modelo de entrada digital com base no erro do teste
            switch (boardId) {
            case JigaTestInterface::ECU1_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU2_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU3_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU4_BOARD_ID:
                switch (i + 1) {
                case 1:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    diInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            }
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::DIGITAL_INPUT_TEST, boardId, testMessage, true);
    }
}

// Verifica e processa o relatório de teste de entrada analógica
void RepBusinessController::checkAnalogInputReport(int boardId, const QString &recvStr)
{
    int code = getTestReportCode(recvStr);
    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        return;
    }

    QVector<int> testResult = UtilsConversion::parseBinary(code);
    QString boardDesc = psController->getBoardDescription(boardId);

    // Processa os resultados individuais do teste de entrada analógica
    for (int i = 0; i < testResult.size(); ++i) {
        QString testMessage;
        if (testResult[i] == 1) {
            testMessage = boardDesc + "->AIN#" + QString::number(i + 1) + ": lida com sucesso!";
            // Atualiza o modelo de entrada analógica com base no resultado do teste
            switch (boardId) {
            case JigaTestInterface::ECU1_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU2_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU3_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU4_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
                break;
            }
        } else {
            testMessage = boardDesc + "->AIN#" + QString::number(i + 1) + ": erro de leitura!";
            // Atualiza o modelo de entrada analógica com base no erro do teste
            switch (boardId) {
            case JigaTestInterface::ECU1_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU2_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU3_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            case JigaTestInterface::ECU4_BOARD_ID:
                switch (i + 1) {
                case 1:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 2:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 3:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case 4:
                    anInputModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
                break;
            }
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::ANALOG_INPUT_TEST, boardId, testMessage, true);
    }
}

// Verifica e processa o relatório de teste de saída analógica
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

    // Verifica o código do teste de saída analógica
    testResult = UtilsConversion::parseBinary(code);

    if (testResult[0] == 1) {
        testMessage = boardDesc + "->AOUT: lida com sucesso!";
        // Atualiza o modelo de saída analógica com base no resultado do teste
        if (boardId == JigaTestInterface::ECU1_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AOUT1_LDR_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
        } else if (boardId == JigaTestInterface::ECU2_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AOUT2_LOOP_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
        }
    } else {
        testMessage = boardDesc + "->AOUT: erro de leitura!";
        // Atualiza o modelo de saída analógica com base no erro do teste
        if (boardId == JigaTestInterface::ECU1_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AOUT1_LDR_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
        } else if (boardId == JigaTestInterface::ECU2_BOARD_ID) {
            anOutputModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AOUT2_LOOP_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
        }
    }

    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::ANALOG_OUTPUT_TEST, boardId, testMessage, true);
}

// Verifica e processa o relatório de inicialização de rede CAN
void RepBusinessController::checkCanInitNetworkReport(int boardId, const QString &recvStr)
{
    int code = getTestReportCode(recvStr);
    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    QVector<int> testResult = UtilsConversion::parseBinary(code);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (testResult[0] == 1) {
        // Atualiza o modelo de inicialização CAN com base no resultado do teste
        switch (boardId) {
        case JigaTestInterface::ECU1_BOARD_ID:
            testMessage = boardDesc + "->CAN1 inicializada com sucesso!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::ICAN1_ECU1_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU2_BOARD_ID:
            testMessage = boardDesc + "->CAN1/CAN2 inicializadas com sucesso!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::ICAN1_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::ICAN2_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU3_BOARD_ID:
            testMessage = boardDesc + "->CAN1 inicializada com sucesso!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::ICAN1_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU4_BOARD_ID:
            testMessage = boardDesc + "->CAN1 inicializada com sucesso!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::ICAN1_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        }
    } else {
        // Atualiza o modelo de inicialização CAN com base no erro do teste
        switch (boardId) {
        case JigaTestInterface::ECU1_BOARD_ID:
            testMessage = boardDesc + "->CAN1 erro de inicialização!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::ICAN1_ECU1_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU2_BOARD_ID:
            testMessage = boardDesc + "->CAN1/CAN2 erro de inicialização!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::ICAN1_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::ICAN2_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU3_BOARD_ID:
            testMessage = boardDesc + "->CAN1 erro de inicialização!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::ICAN1_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU4_BOARD_ID:
            testMessage = boardDesc + "->CAN1 erro de inicialização!";
            canInitModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::ICAN1_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        }
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::CAN_INIT_TEST, boardId, testMessage, true);
}

// Verifica e processa o relatório de teste de loopback CAN
void RepBusinessController::checkLBCanNetworkReport(int boardId, const QString &recvStr)
{
    int code = getTestReportCode(recvStr);
    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    QVector<int> testResult = UtilsConversion::parseBinary(code);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    if (testResult[0] == 1) {
        // Atualiza o modelo de loopback CAN com base no resultado do teste
        switch (boardId) {
        case JigaTestInterface::ECU1_BOARD_ID:
            testMessage = boardDesc + "->CAN1: teste de loopback realizado com sucesso!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::LBC1_ECU1_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU2_BOARD_ID:
            testMessage = boardDesc + "->CAN1/CAN2: testes de loopback realizados com sucesso!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::LBC1_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::LBC2_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU3_BOARD_ID:
            testMessage = boardDesc + "->CAN1: teste de loopback realizado com sucesso!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::LBC1_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU4_BOARD_ID:
            testMessage = boardDesc + "->CAN1: teste de loopback realizado com sucesso!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::LBC1_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            break;
        }
    } else {
        // Atualiza o modelo de loopback CAN com base no erro do teste
        switch (boardId) {
        case JigaTestInterface::ECU1_BOARD_ID:
            testMessage = boardDesc + "->CAN1: erro na execução do teste de loopback!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::LBC1_ECU1_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU2_BOARD_ID:
            testMessage = boardDesc + "->CAN1/CAN2: erro na execução do teste de loopback!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::LBC1_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::LBC2_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU3_BOARD_ID:
            testMessage = boardDesc + "->CAN1: erro na execução do teste de loopback!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::LBC1_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        case JigaTestInterface::ECU4_BOARD_ID:
            testMessage = boardDesc + "->CAN1: erro na execução do teste de loopback!";
            canLoopbackModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::LBC1_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            break;
        }
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::CAN_LOOPBACK_TEST, boardId, testMessage, true);
}


void RepBusinessController::checkC1CanNetworkReport(int boardId, const QString &recvStr)
{
    // Obtém o código do relatório do resultado recebido
    int code = getTestReportCode(recvStr);
    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    // Converte o código para um vetor de inteiros binários representando os resultados dos testes
    QVector<int> testResult = UtilsConversion::parseBinary(code);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    // Verifica os resultados dos testes com base no ID da placa (ECU)
    switch (boardId) {
    case JigaTestInterface::ECU1_BOARD_ID:
        // Para cada resultado do teste, verifica o sucesso ou erro
        for (int i = 0; i < (testResult.size() - 1); ++i) {
            if (testResult[i] == 1) {
                testMessage = QString("%1->CAN1: recebida mensagem de ECU%2").arg(boardDesc).arg(i + 2);
                // Atualiza o modelo com sucesso
                switch (i + 1) {
                case JigaTestInterface::ECU2_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
            } else {
                testMessage = QString("%1->CAN1: erro de mensagem de ECU%2").arg(boardDesc).arg(i + 2);
                // Atualiza o modelo com erro
                switch (i + 1) {
                case JigaTestInterface::ECU2_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
            }
            // Adiciona a mensagem do teste ao relatório
            addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
        break;

    case JigaTestInterface::ECU2_BOARD_ID:
        // Para cada resultado do teste, verifica o sucesso ou erro
        for (int i = 0, offset = 1; i < (testResult.size() - 1); ++i) {
            if (testResult[i] == 1) {
                testMessage = QString("%1->CAN1: recebida mensagem de ECU%2").arg(boardDesc).arg(i + offset);
                // Atualiza o modelo com sucesso
                switch (i + offset - 1) {
                case JigaTestInterface::ECU1_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
            } else {
                testMessage = QString("%1->CAN1: erro de mensagem de ECU%2").arg(boardDesc).arg(i + offset);
                // Atualiza o modelo com erro
                switch (i + offset - 1) {
                case JigaTestInterface::ECU1_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
            }
            if (i == 0) offset = 2;
            // Adiciona a mensagem do teste ao relatório
            addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
        break;

    case JigaTestInterface::ECU3_BOARD_ID:
        // Para cada resultado do teste, verifica o sucesso ou erro
        for (int i = 0, offset = 1; i < (testResult.size() - 1); ++i) {
            if (testResult[i] == 1) {
                testMessage = QString("%1->CAN1: recebida mensagem de ECU%2").arg(boardDesc).arg(i + offset);
                // Atualiza o modelo com sucesso
                switch (i + offset - 1) {
                case JigaTestInterface::ECU1_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU2_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
            } else {
                testMessage = QString("%1->CAN1: erro de mensagem de ECU%2").arg(boardDesc).arg(i + offset);
                // Atualiza o modelo com erro
                switch (i + offset - 1) {
                case JigaTestInterface::ECU1_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU2_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
            }
            if (i >= 1) offset = 2;
            // Adiciona a mensagem do teste ao relatório
            addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
        break;

    case JigaTestInterface::ECU4_BOARD_ID:
        // Para cada resultado do teste, verifica o sucesso ou erro
        for (int i = 0; i < (testResult.size() - 1); ++i) {
            if (testResult[i] == 1) {
                testMessage = QString("%1->CAN1: recebida mensagem de ECU%2").arg(boardDesc).arg(i + 1);
                // Atualiza o modelo com sucesso
                switch (i) {
                case JigaTestInterface::ECU1_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU2_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
            } else {
                testMessage = QString("%1->CAN1: erro de mensagem de ECU%2").arg(boardDesc).arg(i + 1);
                // Atualiza o modelo com erro
                switch (i) {
                case JigaTestInterface::ECU1_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU2_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c1NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
            }
            // Adiciona a mensagem do teste ao relatório
            addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, boardId, testMessage, true);
        }
        break;
    }
}

void RepBusinessController::checkC2CanNetworkReport(int boardId, const QString &recvStr) {
    // Obtém o código do relatório do resultado recebido
    int code = getTestReportCode(recvStr);
    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    // Converte o código para um vetor de inteiros binários representando os resultados dos testes
    QVector<int> testResult = UtilsConversion::parseBinary(code);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    // Verifica os resultados dos testes com base no ID da placa (ECU)
    switch (boardId) {
    case JigaTestInterface::ECU2_BOARD_ID:
        // Para cada resultado do teste, verifica o sucesso ou erro
        for (int i = 0; i < (testResult.size() - 2); ++i) {
            if (testResult[i] == 1) {
                testMessage = QString("%1->CAN2: mensagem recebida da ECU%2").arg(boardDesc).arg(i + 3);
                // Atualiza o modelo com sucesso
                switch (i + 2) {
                case JigaTestInterface::ECU3_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN2_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN2_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
            } else {
                testMessage = QString("%1->CAN2: erro de mensagem da ECU%2").arg(boardDesc).arg(i + 3);
                // Atualiza o modelo com erro
                switch (i + 2) {
                case JigaTestInterface::ECU3_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN2_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN2_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
            }
            // Adiciona a mensagem do teste ao relatório
            addCmdTestMessage(JigaTestInterface::CAN2_NETWORK_TEST, boardId, testMessage, true);
        }
        break;

    case JigaTestInterface::ECU3_BOARD_ID:
        // Para cada resultado do teste, verifica o sucesso ou erro
        for (int i = 0, offset = 2; i < (testResult.size() - 2); ++i) {
            if (testResult[i] == 1) {
                testMessage = QString("%1->CAN2: mensagem recebida da ECU%2").arg(boardDesc).arg(i + offset);
                // Atualiza o modelo com sucesso
                switch (i + offset - 1) {
                case JigaTestInterface::ECU2_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN2_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN2_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
            } else {
                testMessage = QString("%1->CAN2: erro de mensagem da ECU%2").arg(boardDesc).arg(i + offset);
                // Atualiza o modelo com erro
                switch (i + offset - 1) {
                case JigaTestInterface::ECU2_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN2_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN2_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
            }
            if (i == 0) offset = 3;
            // Adiciona a mensagem do teste ao relatório
            addCmdTestMessage(JigaTestInterface::CAN2_NETWORK_TEST, boardId, testMessage, true);
        }
        break;

    case JigaTestInterface::ECU4_BOARD_ID:
        // Para cada resultado do teste, verifica o sucesso ou erro
        for (int i = 0; i < (testResult.size() - 2); ++i) {
            if (testResult[i] == 1) {
                testMessage = QString("%1->CAN2: mensagem recebida da ECU%2").arg(boardDesc).arg(i + 2);
                // Atualiza o modelo com sucesso
                switch (i + 1) {
                case JigaTestInterface::ECU2_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN2_ECU2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN2_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                    break;
                }
            } else {
                testMessage = QString("%1->CAN2: erro de mensagem da ECU%2").arg(boardDesc).arg(i + 2);
                // Atualiza o modelo com erro
                switch (i + 1) {
                case JigaTestInterface::ECU2_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN2_ECU2_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    c2NetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN2_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
                    break;
                }
            }
            // Adiciona a mensagem do teste ao relatório
            addCmdTestMessage(JigaTestInterface::CAN2_NETWORK_TEST, boardId, testMessage, true);
        }
        break;
    }
}

void RepBusinessController::checkLinNetworkReport(int boardId, const QString &recvStr) {
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(boardId);
    QString testMessage;

    // Verifica se houve erro ao obter o código do relatório
    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "Error to read report code!";
        return;
    }

    // Converte o código para um vetor de inteiros binários representando os resultados dos testes
    testResult = UtilsConversion::parseBinary(code);

    int lnSize = lnNetworkModel->getSize(); // Obtém o tamanho da rede LIN
    // Para cada resultado do teste, verifica o sucesso ou erro
    for (int i = 0; i < (lnSize - 2); i++) {
        if (testResult[i] == 1) {
            testMessage = boardDesc + "->LIN: Mensagem lida com sucesso!";
            // Atualiza o modelo com sucesso
            if (boardId == JigaTestInterface::ECU3_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::LIN1_ECU3_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            } else if (boardId == JigaTestInterface::ECU4_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::LIN1_ECU4_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            }
        } else {
            testMessage = boardDesc + "->LIN: Erro na leitura da mensagem!";
            // Atualiza o modelo com erro
            if (boardId == JigaTestInterface::ECU3_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::LIN1_ECU3_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            } else if (boardId == JigaTestInterface::ECU4_BOARD_ID) {
                lnNetworkModel->setIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::LIN1_ECU4_ITEST, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            }
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::LIN_NETWORK_TEST, boardId, testMessage, true);
    }
}

void RepBusinessController::checkMcuGetCanBusReport(const QString &recvStr) {
    QVector<int> testResult;
    int code = getTestReportCode(recvStr);
    QString boardDesc = psController->getBoardDescription(JigaTestInterface::MCU1_BOARD_ID);
    QString testMessage;

    // Verifica se houve erro ao obter o código do relatório
    if (code == EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
        qDebug() << "RepBusinessController: Board =" << boardDesc << "error to read report code!";
        qDebug() << "Serial output:" << recvStr;
        return;
    }

    // Converte o código para um vetor de inteiros binários representando os resultados dos testes
    testResult = UtilsConversion::parseBinary(code);

    // Verifica a conexão da ECU3 ao CANBUS
    if (testResult[0] == 0) {
        testMessage = boardDesc + "-> ECU3 conectada no CANBUS1!";
        Ecu3Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_1);
    } else {
        testMessage = boardDesc + "-> ECU3 conectada no CANBUS2!";
        Ecu3Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_2);
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::MCU_GET_CANBUS_TEST, JigaTestInterface::MCU1_BOARD_ID, testMessage, true);

    // Verifica a conexão da ECU4 ao CANBUS
    if (testResult[1] == 0) {
        testMessage = boardDesc + "-> ECU4 conectada no CANBUS1!";
        Ecu4Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_1);
    } else {
        testMessage = boardDesc + "-> ECU4 conectada no CANBUS2!";
        Ecu4Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_2);
    }
    // Adiciona a mensagem do teste ao relatório e marca o teste como bem-sucedido
    addCmdTestMessage(JigaTestInterface::MCU_GET_CANBUS_TEST, JigaTestInterface::MCU1_BOARD_ID, testMessage, true);
    mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::MCU_GET_CANBUS_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
}

void RepBusinessController::showCommunicationTestReport() {
    int testResult;
    QString reportMessage;

    qDebug() << "Passou";
    // Verificando Teste de Comunicação - ECU1
    testResult = commTestModel->getIndividualTestResult(JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::COMM_ECU1_ITEST);

    if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
        reportMessage = psController->getReportProperty("com.ecu1.err");
    } else {
        reportMessage = QString("%1 com a ECU1 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::ECU1_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - ECU2
    testResult = commTestModel->getIndividualTestResult(JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::COMM_ECU2_ITEST);
    if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
        reportMessage = psController->getReportProperty("com.ecu2.err");
    } else {
        reportMessage = QString("%1 com a ECU2 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::ECU2_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - ECU3
    testResult = commTestModel->getIndividualTestResult(JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::COMM_ECU3_ITEST);
    if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
        reportMessage = psController->getReportProperty("com.ecu3.err");
    } else {
        reportMessage = QString("%1 com a ECU3 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::ECU3_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - ECU4
    testResult = commTestModel->getIndividualTestResult(JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::COMM_ECU4_ITEST);
    if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
        reportMessage = psController->getReportProperty("com.ecu4.err");
    } else {
        reportMessage = QString("%1 com a ECU4 realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::ECU4_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - PROG
    testResult = commTestModel->getIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::COMM_PROG_ITEST);
    if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
        reportMessage = psController->getReportProperty("com.prog.err");
    } else {
        reportMessage = QString("%1 com o PROG realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::MCU1_BOARD_ID, reportMessage, true);

    // Verificando Teste de Comunicação - MCU1
    testResult = commTestModel->getIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::COMM_MCU1_ITEST);
    if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
        reportMessage = psController->getReportProperty("com.mcu1.err");
    } else {
        reportMessage = QString("%1 com o PROG realizado com sucesso!").arg(CmdMessageConstants::CMD_MSG_COMMUNICATION);
    }
    // Adiciona a mensagem do teste ao relatório
    addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::MCU1_BOARD_ID, reportMessage, true);
}

void RepBusinessController::showDigitalInputTestReport()
{
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para entradas digitais
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, SystemProperties::REP_DIN1T_ECU1_ERR, "ECU1 DIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, SystemProperties::REP_DIN2T_ECU1_ERR, "ECU1 DIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, SystemProperties::REP_DIN3T_ECU1_ERR, "ECU1 DIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, SystemProperties::REP_DIN4T_ECU1_ERR, "ECU1 DIN#4 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, SystemProperties::REP_DIN1T_ECU2_ERR, "ECU2 DIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, SystemProperties::REP_DIN2T_ECU2_ERR, "ECU2 DIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, SystemProperties::REP_DIN3T_ECU2_ERR, "ECU2 DIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, SystemProperties::REP_DIN4T_ECU2_ERR, "ECU2 DIN#4 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, SystemProperties::REP_DIN1T_ECU3_ERR, "ECU3 DIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, SystemProperties::REP_DIN2T_ECU3_ERR, "ECU3 DIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, SystemProperties::REP_DIN3T_ECU3_ERR, "ECU3 DIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, SystemProperties::REP_DIN4T_ECU3_ERR, "ECU3 DIN#4 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN1_INPUT_ITEST, SystemProperties::REP_DIN1T_ECU4_ERR, "ECU4 DIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN2_INPUT_ITEST, SystemProperties::REP_DIN2T_ECU4_ERR, "ECU4 DIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN3_INPUT_ITEST, SystemProperties::REP_DIN3T_ECU4_ERR, "ECU4 DIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::DIN4_INPUT_ITEST, SystemProperties::REP_DIN4T_ECU4_ERR, "ECU4 DIN#4 lida com sucesso!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = diInputModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_DIGITAL_INPUT) + ": " + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::DIGITAL_INPUT_TEST, detail.boardId, reportMessage, true);
    }
}

void RepBusinessController::showAnalogInputTestReport() {
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para entradas analógicas
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, SystemProperties::REP_AIN1T_ECU1_ERR, "ECU1 AIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, SystemProperties::REP_AIN2T_ECU1_ERR, "ECU1 AIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, SystemProperties::REP_AIN3T_ECU1_ERR, "ECU1 AIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, SystemProperties::REP_AIN4T_ECU1_ERR, "ECU1 AIN#4 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, SystemProperties::REP_AIN1T_ECU2_ERR, "ECU2 AIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, SystemProperties::REP_AIN2T_ECU2_ERR, "ECU2 AIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, SystemProperties::REP_AIN3T_ECU2_ERR, "ECU2 AIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, SystemProperties::REP_AIN4T_ECU2_ERR, "ECU2 AIN#4 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, SystemProperties::REP_AIN1T_ECU3_ERR, "ECU3 AIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, SystemProperties::REP_AIN2T_ECU3_ERR, "ECU3 AIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, SystemProperties::REP_AIN3T_ECU3_ERR, "ECU3 AIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, SystemProperties::REP_AIN4T_ECU3_ERR, "ECU3 AIN#4 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN1_INPUT_ITEST, SystemProperties::REP_AIN1T_ECU4_ERR, "ECU4 AIN#1 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN2_INPUT_ITEST, SystemProperties::REP_AIN2T_ECU4_ERR, "ECU4 AIN#2 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN3_INPUT_ITEST, SystemProperties::REP_AIN3T_ECU4_ERR, "ECU4 AIN#3 lida com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::AIN4_INPUT_ITEST, SystemProperties::REP_AIN4T_ECU4_ERR, "ECU4 AIN#4 lida com sucesso!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = anInputModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_ANALOG_INPUT) + ": " + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::ANALOG_INPUT_TEST, detail.boardId, reportMessage, true);
    }
}

void RepBusinessController::showAnalogOutputTestReport() {
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para saídas analógicas
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::AOUT1_LDR_ITEST, SystemProperties::REP_ANOUT_ECU1_ERR, "AOUT#1 realizado com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::AOUT2_LOOP_ITEST, SystemProperties::REP_ANOUT_ECU2_ERR, "AOUT#2 realizado com sucesso!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = anOutputModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_ANALOG_OUTPUT) + " " + anOutputModel->getBoardDescription(detail.boardId) + " " + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::ANALOG_OUTPUT_TEST, detail.boardId, reportMessage, true);
    }
}

void RepBusinessController::showCanInitTestReport() {
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para inicialização CAN
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::ICAN1_ECU1_ITEST, SystemProperties::REP_CANIT_ECU1_ERR, "CAN1 da ECU1 realizado com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::ICAN1_ECU2_ITEST, SystemProperties::REP_CANIT_ECU2C1_ERR, "CAN1 da ECU2 realizado com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::ICAN2_ECU2_ITEST, SystemProperties::REP_CANIT_ECU2C2_ERR, "CAN2 da ECU2 realizado com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::ICAN1_ECU3_ITEST, SystemProperties::REP_CANIT_ECU3_ERR, "CAN1 da ECU3 realizado com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::ICAN1_ECU4_ITEST, SystemProperties::REP_CANIT_ECU4_ERR, "CAN1 da ECU4 realizado com sucesso!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = canInitModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_CAN_INIT) + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::CAN_INIT_TEST, detail.boardId, reportMessage, true);
    }
}

void RepBusinessController::showCanLoopbackTestReport() {
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para loopback CAN
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::LBC1_ECU1_ITEST, SystemProperties::REP_CAN1L_ECU1_ERR, "CAN1 da ECU1 realizado com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::LBC1_ECU2_ITEST, SystemProperties::REP_CAN1L_ECU2_ERR, "CAN1 da ECU2 realizado com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::LBC2_ECU2_ITEST, SystemProperties::REP_CAN2L_ECU2_ERR, "CAN2 da ECU2 realizado com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::LBC1_ECU3_ITEST, SystemProperties::REP_CAN1L_ECU3_ERR, "CAN1 da ECU3 realizado com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::LBC1_ECU4_ITEST, SystemProperties::REP_CAN1L_ECU4_ERR, "CAN1 da ECU4 realizado com sucesso!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = canLoopbackModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_LOOPBACK_CAN) + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::CAN_LOOPBACK_TEST, detail.boardId, reportMessage, true);
    }
}

void RepBusinessController::showCan1NetworkTestReport() {
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para a rede CAN1
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, SystemProperties::REP_CAN1T_EC12_ERR, "ECU1 recebeu mensagem da ECU2 com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, SystemProperties::REP_CAN1T_EC13_ERR, "ECU1 recebeu mensagem da ECU3 com sucesso!"},
        {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, SystemProperties::REP_CAN1T_EC14_ERR, "ECU1 recebeu mensagem da ECU4 com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, SystemProperties::REP_CAN1T_EC21_ERR, "ECU2 recebeu mensagem da ECU1 com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, SystemProperties::REP_CAN1T_EC23_ERR, "ECU2 recebeu mensagem da ECU3 com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, SystemProperties::REP_CAN1T_EC24_ERR, "ECU2 recebeu mensagem da ECU4 com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, SystemProperties::REP_CAN1T_EC31_ERR, "ECU3 recebeu mensagem da ECU1 com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, SystemProperties::REP_CAN1T_EC32_ERR, "ECU3 recebeu mensagem da ECU2 com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN1_ECU4_ITEST, SystemProperties::REP_CAN1T_EC34_ERR, "ECU3 recebeu mensagem da ECU4 com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU1_ITEST, SystemProperties::REP_CAN1T_EC41_ERR, "ECU4 recebeu mensagem da ECU1 com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU2_ITEST, SystemProperties::REP_CAN1T_EC42_ERR, "ECU4 recebeu mensagem da ECU2 com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN1_ECU3_ITEST, SystemProperties::REP_CAN1T_EC43_ERR, "ECU4 recebeu mensagem da ECU3 com sucesso!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = c1NetworkModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_CAN1_NETWORK) + ": " + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, detail.boardId, reportMessage, true);
    }
}

void RepBusinessController::showCan2NetworkTestReport() {
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para a rede CAN2
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN2_ECU3_ITEST, SystemProperties::REP_CAN2T_EC23_ERR, "ECU2 recebeu a mensagem da ECU3 com sucesso!"},
        {JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::CAN2_ECU4_ITEST, SystemProperties::REP_CAN2T_EC24_ERR, "ECU2 recebeu a mensagem da ECU4 com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN2_ECU2_ITEST, SystemProperties::REP_CAN2T_EC32_ERR, "ECU3 recebeu a mensagem da ECU2 com sucesso!"},
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::CAN2_ECU4_ITEST, SystemProperties::REP_CAN2T_EC34_ERR, "ECU3 recebeu a mensagem da ECU4 com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN2_ECU2_ITEST, SystemProperties::REP_CAN2T_EC42_ERR, "ECU4 recebeu a mensagem da ECU2 com sucesso!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::CAN2_ECU3_ITEST, SystemProperties::REP_CAN2T_EC43_ERR, "ECU4 recebeu a mensagem da ECU3 com sucesso!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = c2NetworkModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_CAN2_NETWORK) + ": " + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::CAN2_NETWORK_TEST, detail.boardId, reportMessage, true);
    }
}

void RepBusinessController::showLinNetworkTestReport() {
    int testResult;
    QString reportMessage;

    struct TestDetails {
        int boardId;
        int testId;
        QString errorMsg;
        QString successMsg;
    };

    // Cria um vetor de detalhes de testes para a rede LIN
    QVector<TestDetails> testDetails = {
        {JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::LIN1_ECU3_ITEST, SystemProperties::REP_LINNT_EC34_ERR, "ECU3 recebeu mensagem LIN da ECU4!"},
        {JigaTestInterface::ECU4_BOARD_ID, JigaTestInterface::LIN1_ECU4_ITEST, SystemProperties::REP_LINNT_EC43_ERR, "ECU4 recebeu mensagem LIN da ECU3!"}
    };

    // Verifica os resultados dos testes e cria relatórios
    for (const auto& detail : testDetails) {
        testResult = lnNetworkModel->getIndividualTestResult(detail.boardId, detail.testId);
        if (testResult == JigaTestInterface::ERROR_TO_EXECUTE_TEST) {
            reportMessage = psController->getReportProperty(detail.errorMsg);
        } else {
            reportMessage = QString(CmdMessageConstants::CMD_MSG_LIN_NETWORK) + ": " + detail.successMsg;
        }
        // Adiciona a mensagem do teste ao relatório
        addCmdTestMessage(JigaTestInterface::LIN_NETWORK_TEST, detail.boardId, reportMessage, true);
    }
}
