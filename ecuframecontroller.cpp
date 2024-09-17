#include "EcuFrameController.h"
#include <QDebug>

EcuFrameController::EcuFrameController(QObject *parent)
    : FrameController(parent) {
    // Configura os modelos utilizados pelo controlador
    setupModels();

    // Inicializa o controlador de negócios ECU
    bsController = new EcuBusinessController();
}

EcuFrameController::~EcuFrameController() {
    // Código de limpeza, se necessário
}

void EcuFrameController::setupModels() {
    // Adiciona listeners de mudança a todos os modelos relacionados
    commTestModel->addChangeListeners(this);
    diInputModel->addChangeListeners(this);
    anInputModel->addChangeListeners(this);
    anOutputModel->addChangeListeners(this);
    canInitModel->addChangeListeners(this);
    lbNetworkModel->addChangeListeners(this);
    c1NetworkModel->addChangeListeners(this);
    c2NetworkModel->addChangeListeners(this);
    lnNetworkModel->addChangeListeners(this);
    mcuFwUpModel->addChangeListeners(this);
    mcu1TestModel->addChangeListeners(this);
}

void EcuFrameController::executeTest(int testId, int boardId) {
    // Verifica se o controlador de negócios 'bsController' foi inicializado
    if (bsController == nullptr) {
        qDebug() << "Erro: bsController não inicializado";
            return;
    }
    // Verifica se o modelo de teste de comunicação 'commTestModel' foi inicializado
    if (commTestModel == nullptr) {
        qDebug() << "Erro: commTestModel não inicializado";
            return;
    }

    int boardLoaded;
    bool testStarted;
    QString testMessage;

    // 1 - Reseta o modelo de teste para o ID fornecido
    this->resetTestModel(testId);

    // 2 - Adiciona uma mensagem de início de teste com base no ID da placa
    if (boardId == JigaTestInterface::MCU1_BOARD_ID) {  // 4
        testMessage = " iniciada!";
    } else {
        testMessage = " iniciado!";
    }
    this->addHeaderTestMessage(testId, boardId, testMessage);

    qDebug() << "Chamando loadBoard";

    // 3 - Carrega as informações da placa usando o controlador de negócios
    boardLoaded = bsController->loadBoard(testId, boardId);

    // Verifica se o carregamento da placa foi bem-sucedido
    if (boardLoaded != ErrorCodeInterface::SUCCESS) {
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
        bsController->addCmdTestMessage(testId, boardId, testMessage, true);
        return;
    }

    // 4 - Inicia o teste individual da placa
    testStarted = bsController->startIndividualBoardTest(testId, boardId);

    // Verifica se o teste começou corretamente
    if (!testStarted) {
        // Erro ao executar o teste
        testMessage = CmdMessageConstants::MSG_ERROR_TO_RUN_TEST + commTestModel->getBoardDescription(boardId);
        bsController->addCmdTestMessage(testId, boardId, testMessage, true);
        commTestModel->setTestResult(boardId, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
    } else {
        waitReportTestTimeOut(testId, 0, boardId);  // Aguarda o tempo limite do teste
    }

    // 5 - Adiciona uma mensagem de fim de teste
    this->addHeaderTestMessage(testId, boardId, " finalizado!");
}

void EcuFrameController::executeTest(int test_id)
{
    int numberOfBoards;
    QString testMessage;

    if (!bsController) {
        qWarning() << "Business controller not set.";
        return;
    }

    // 1 - Reseta as condições do modelo de teste
    resetTestModel(test_id);

    // 2 - Adiciona uma mensagem de início de teste
    testMessage = " iniciado!";
    addHeaderTestMessage(test_id, JigaTestInterface::ALL_BOARDS_ID, testMessage);

    // 3 - Carrega informações de todas as placas
    numberOfBoards = bsController->loadAllBoards(test_id);
    if (numberOfBoards == 0) {
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
        bsController->addCmdTestMessage(test_id, JigaTestInterface::ALL_BOARDS_ID, testMessage, true);
        return;
    }

    // 4 - Inicia o teste coletivo das placas baseado no ID do teste
    switch (test_id) {
    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        executeAnalogOutputTest();
        break;
    case JigaTestInterface::LIN_NETWORK_TEST:
        executeLinNetworkTest();
        break;
    case JigaTestInterface::CAN_INIT_TEST:
        executeCanInitTest();
        break;
    case JigaTestInterface::CAN1_NETWORK_TEST:
        executeCan1NetworkTest();
        break;
    case JigaTestInterface::CAN2_NETWORK_TEST:
        executeCan2NetworkTest();
        break;
    case JigaTestInterface::COMMUNICATION_TEST:
        executeCommunicationTest();
        break;
    case JigaTestInterface::DIGITAL_INPUT_TEST:
        executeDigitalInputTest();
        break;
    case JigaTestInterface::ANALOG_INPUT_TEST:
        executeAnalogInputTest();
        break;
    case JigaTestInterface::CAN_LOOPBACK_TEST:
        executeLoopbackCanTest();
        break;
    default:
        qDebug() << "Unknown test ID:" << test_id;
        break;
    }

    // 5 - Adiciona uma mensagem de fim de teste
    addHeaderTestMessage(test_id, JigaTestInterface::ALL_BOARDS_ID, " finalizado!");
}

void EcuFrameController::executeTestReport(int test_id)
{
    // Executa relatórios de teste baseados no ID do teste
    switch (test_id) {
    case JigaTestInterface::COMMUNICATION_TEST:
        rpController->showCommunicationTestReport();
        break;
    case JigaTestInterface::DIGITAL_INPUT_TEST:
        rpController->showDigitalInputTestReport();
        break;
    case JigaTestInterface::ANALOG_INPUT_TEST:
        rpController->showAnalogInputTestReport();
        break;
    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        rpController->showAnalogOutputTestReport();
        break;
    case JigaTestInterface::CAN_INIT_TEST:
        rpController->showCanInitTestReport();
        break;
    case JigaTestInterface::CAN_LOOPBACK_TEST:
        rpController->showCanLoopbackTestReport();
        break;
    case JigaTestInterface::CAN1_NETWORK_TEST:
        rpController->showCan1NetworkTestReport();
        break;
    case JigaTestInterface::CAN2_NETWORK_TEST:
        rpController->showCan2NetworkTestReport();
        break;
    case JigaTestInterface::LIN_NETWORK_TEST:
        rpController->showLinNetworkTestReport();
        break;
    default:
        qWarning() << "Test ID não reconhecido:" << test_id;
            break;
    }
}

void EcuFrameController::executeCommunicationTest()
{
    QString testMessage;
    bool testStarted;

    // Itera por todas as ECUs para executar o teste de comunicação
    for (int i = 0; i < JigaTestInterface::MAX_NUMBER_ECUS; ++i) {
        testStarted = bsController->startIndividualBoardTest(JigaTestInterface::COMMUNICATION_TEST, i);
        if (!testStarted) {
            // Erro ao executar o teste
            commTestModel->setTestResult(i, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            testMessage = QString(CmdMessageConstants::CMD_ERROR_TEST_EXECUTION) + " (" + commTestModel->getBoardDescription(i) + ")";
            bsController->addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, i, testMessage, true);
        } else {
            commTestModel->setTestResult(i, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            testMessage = QString(CmdMessageConstants::CMD_SUCCESS_TEST_EXECUTION) + " (" + commTestModel->getBoardDescription(i) + ")";
            bsController->addCmdTestMessage(JigaTestInterface::COMMUNICATION_TEST, i, testMessage, true);
        }
    }
}

void EcuFrameController::executeCan1NetworkTest() {
    // Lambda para encapsular a lógica de teste para facilitar a reutilização
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

    // Tentativa de configurar CANBUS1 para ECUs
    if (!handleTest(JigaTestInterface::MCU_SEL_CANBUS1_TEST, JigaTestInterface::MCU1_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU4_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU1_BOARD_ID)) return;

    // Adiciona mensagem indicando que está aguardando resultados do teste
    bsController->addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::CAN_NETWORK_TEST_OFFSET, JigaTestInterface::ALL_BOARDS_ID);
}

void EcuFrameController::executeCan2NetworkTest()
{
    // Lambda para encapsular a lógica de teste para facilitar a reutilização
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

    // Tentativa de configurar CANBUS2 para ECUs
    if (!handleTest(JigaTestInterface::MCU_SEL_CANBUS2_TEST, JigaTestInterface::MCU1_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN2_NETWORK_TEST, JigaTestInterface::ECU4_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN2_NETWORK_TEST, JigaTestInterface::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN2_NETWORK_TEST, JigaTestInterface::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN2_NETWORK_TEST, JigaTestInterface::ECU1_BOARD_ID)) return;

    // Adiciona mensagem indicando que está aguardando resultados do teste
    bsController->addCmdTestMessage(JigaTestInterface::CAN2_NETWORK_TEST, JigaTestInterface::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestInterface::CAN2_NETWORK_TEST, JigaTestInterface::CAN_NETWORK_TEST_OFFSET, JigaTestInterface::ALL_BOARDS_ID);
}

void EcuFrameController::executeDigitalInputTest() {
    QString testMessage;
    bool testStarted;

    // Itera por todas as ECUs para executar o teste de entrada digital
    for (int i = 0; i < JigaTestInterface::MAX_NUMBER_ECUS; ++i) {
        testStarted = bsController->startIndividualBoardTest(JigaTestInterface::DIGITAL_INPUT_TEST, i);
        if (!testStarted) {
            // Erro ao executar o teste
            diInputModel->setTestResult(i, JigaTestInterface::ERROR_TO_EXECUTE_TEST);
            testMessage = QString(CmdMessageConstants::CMD_ERROR_TEST_EXECUTION) + " (" + diInputModel->getBoardDescription(i) + ")";
            bsController->addCmdTestMessage(JigaTestInterface::DIGITAL_INPUT_TEST, i, testMessage, true);
        } else {
            diInputModel->setTestResult(i, JigaTestInterface::SUCCESS_EXECUTE_TEST);
            testMessage = QString(CmdMessageConstants::CMD_SUCCESS_TEST_EXECUTION) + " (" + diInputModel->getBoardDescription(i) + ")";
            bsController->addCmdTestMessage(JigaTestInterface::DIGITAL_INPUT_TEST, i, testMessage, true);
        }
    }

    // Adiciona mensagem indicando que está aguardando resultados do teste
    bsController->addCmdTestMessage(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_DIGITAL_TEST, true);
    waitReportTestTimeOut(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::DIGITAL_INPUT_TEST_OFFSET, JigaTestInterface::ALL_BOARDS_ID);
}

void EcuFrameController::executeAnalogOutputTest()
{
    // Lambda para encapsular a lógica de teste para facilitar a reutilização
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

    // Executa o teste de saída analógica para ECU1 e ECU2
    if (!handleTest(JigaTestInterface::ANALOG_OUTPUT_TEST, JigaTestInterface::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::ANALOG_OUTPUT_TEST, JigaTestInterface::ECU1_BOARD_ID)) return;

    // Adiciona mensagem indicando que está aguardando resultados do teste
    bsController->addCmdTestMessage(JigaTestInterface::ANALOG_OUTPUT_TEST, JigaTestInterface::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestInterface::ANALOG_OUTPUT_TEST, JigaTestInterface::ANALOG_OUTPUT_TEST_OFFSET, JigaTestInterface::ALL_BOARDS_ID);
}

void EcuFrameController::executeLinNetworkTest()
{
    // Lambda para encapsular a lógica de teste para facilitar a reutilização
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

    // Executa o teste de rede LIN para ECU3 e ECU4
    if (!handleTest(JigaTestInterface::LIN_NETWORK_TEST, JigaTestInterface::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::LIN_NETWORK_TEST, JigaTestInterface::ECU4_BOARD_ID)) return;

    // Adiciona mensagem indicando que está aguardando resultados do teste
    bsController->addCmdTestMessage(JigaTestInterface::LIN_NETWORK_TEST, JigaTestInterface::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestInterface::LIN_NETWORK_TEST, JigaTestInterface::LIN_NETWORK_TEST_OFFSET, JigaTestInterface::ALL_BOARDS_ID);
}

void EcuFrameController::executeCanInitTest()
{
    // Lambda para encapsular a lógica de teste para facilitar a reutilização
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

    // Executa o teste de inicialização CAN para ECU1 a ECU4
    if (!handleTest(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU1_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU4_BOARD_ID)) return;
}

void EcuFrameController::executeLoopbackCanTest()
{
    // Lambda para encapsular a lógica de teste para facilitar a reutilização
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            lbNetworkModel->setTestResult(boardId, JigaTestInterface::CAN_LOOPBACK_TEST);
            return false;
        } else {
            bsController->addCmdTestMessage(testId, boardId, CmdMessageConstants::MSG_SUCCESS_START_TEST, true);
            return true;
        }
    };

    // Executa o teste de loopback CAN para cada ECU
    if (!handleTest(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU1_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU4_BOARD_ID)) return;

    // Adiciona mensagem indicando que está aguardando resultados do teste
    bsController->addCmdTestMessage(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_TEST_RESULT, true);
    waitReportTestTimeOut(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::CAN_NETWORK_TEST_OFFSET, JigaTestInterface::ALL_BOARDS_ID);
}

void EcuFrameController::executeAnalogInputTest()
{
    // Lambda para encapsular a lógica de teste para facilitar a reutilização
    auto handleTest = [this](int testId, int boardId) {
        QString testMessage;
        bool testStarted = bsController->startIndividualBoardTest(testId, boardId);
        if (!testStarted) {
            testMessage = QString(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + commTestModel->getBoardDescription(boardId);
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
            // Presumindo que diInputModel pode definir resultados do teste, se necessário
            diInputModel->setTestResult(boardId, EcuBusinessInterface::ERROR_COMMUNICATION_TEST);
        } else {
            testMessage = QString(CmdMessageConstants::CMD_SUCCESS_TEST_EXECUTION) + " (" + commTestModel->getBoardDescription(boardId) + ")";
            bsController->addCmdTestMessage(testId, boardId, testMessage, true);
        }
        return testStarted;
    };

    // Executa o teste de entrada analógica para todas as ECUs designadas
    if (!handleTest(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU1_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU2_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU3_BOARD_ID)) return;
    if (!handleTest(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU4_BOARD_ID)) return;

    // Após todos os testes terem sido iniciados, envia uma mensagem indicando que o sistema está aguardando resultados
    bsController->addCmdTestMessage(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ALL_BOARDS_ID, CmdMessageConstants::MSG_WAITING_ANALOG_TEST, true);

    // Implementa a espera pelo relatório do teste com base em um timeout especificado nas constantes
    waitReportTestTimeOut(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ANALOG_INPUT_TEST_OFFSET, JigaTestInterface::ALL_BOARDS_ID);
}

void EcuFrameController::executeFirmwareUpload(int board_id, int processor_id) {
    int retVal;
    QString testMessage;

    // 1 - Reseta as condições do modelo de teste
    resetTestModel(JigaTestInterface::ECU_FIRMWARE_UPLOAD);

    // 2 - Adiciona uma mensagem de início de teste
    testMessage = " iniciada!";
    addHeaderTestMessage(JigaTestInterface::ECU_FIRMWARE_UPLOAD, board_id, testMessage);

    // 3 - Carrega as portas de comunicação serial
    retVal = bsController->loadSerialCommPorts();
    if (retVal <= 0) {
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
        bsController->addCmdTestMessage(JigaTestInterface::ECU_FIRMWARE_UPLOAD, board_id, testMessage, true);
        return;
    }

    // Verifica o ID da placa
    if (board_id == JigaTestInterface::ALL_BOARDS_ID) {
        // Itera sobre todos os IDs de placa
        const QList<int> boardIds = {JigaTestInterface::ECU1_BOARD_ID, JigaTestInterface::ECU2_BOARD_ID, JigaTestInterface::ECU3_BOARD_ID, JigaTestInterface::ECU4_BOARD_ID};
        for (int id : boardIds) {
            // Envia um reset externo com timeout
            bsController->startIndividualBoardTest(JigaTestInterface::MCU_RST_ATT_TEST, JigaTestInterface::MCU1_BOARD_ID);
            // Inicia o upload do firmware
            bsController->uploadFirmware(id, processor_id);
        }
    } else {
        // Envia um reset externo com timeout
        bsController->startIndividualBoardTest(JigaTestInterface::MCU_RST_ATT_TEST, JigaTestInterface::MCU1_BOARD_ID);
        // Inicia o upload do firmware
        bsController->uploadFirmware(board_id, processor_id);
    }

    // Adiciona uma mensagem de finalização do teste
    addHeaderTestMessage(JigaTestInterface::ECU_FIRMWARE_UPLOAD, board_id, " finalizada!");
}

// Método que define o controlador de negócios da ECU
void EcuFrameController::setEcuBusinessController(EcuBusinessController bsInterface)
{
    this->bsController = &bsInterface;
}

void EcuFrameController::executeFindSerialPortTest()
{
    int retVal;
    QString testMessage;

    // 1 - Reseta as condições do modelo de teste
    resetTestModel(JigaTestInterface::FIND_SERIAL_PORT_TEST);

    // 2 - Adiciona uma mensagem de início de teste
    testMessage = " iniciada!";
    addHeaderTestMessage(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::ALL_BOARDS_ID, testMessage);

    // 3 - Encontra todas as portas de comunicação serial
    retVal = bsController->findSerialCommPorts();
    if (retVal < 0) {
        testMessage = CmdMessageConstants::MSG_UNAVAILABLE_SERIAL_PORT;
        bsController->addCmdTestMessage(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::ALL_BOARDS_ID, testMessage, true);
        return;
    }

    // Adiciona uma mensagem de finalização do teste
    addHeaderTestMessage(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::ALL_BOARDS_ID, " finalizada!");
}

// Retorna informações sobre as portas de comunicação serial
QVector<SerialCommPort*> EcuFrameController::getSerialCommPortsInfo()
{
    return bsController->getSerialCommPortsInfo();
}

// Método que lida com o timeout de um teste
void EcuFrameController::handleTimeout() {
    qDebug() << "Test timeout occurred";
    // Lida com o timeout do teste
}

// Método que aguarda o timeout do relatório de teste
void EcuFrameController::waitReportTestTimeOut(int test_id, int offset, int board_id) {
    // Assegura que 'board_id' seja capturado por valor para uso após a saída da função
    QTimer::singleShot(offset * 1000, this, [this, test_id, board_id]() {
        emit testFinished(test_id, board_id, "Test timeout occurred.");
    });
}
