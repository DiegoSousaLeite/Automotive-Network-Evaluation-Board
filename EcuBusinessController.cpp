#include "EcuBusinessController.h"
#include <QThread>
#include <QDebug>

// Construtor da classe EcuBusinessController
EcuBusinessController::EcuBusinessController(QObject *parent)
    : BusinessController(parent), repController(nullptr) {
    // Inicializa o controlador de persistência
    psController = new PersistenceController();
}

// Inicia um teste individual na placa especificada
bool EcuBusinessController::startIndividualBoardTest(int testId, int boardId) {
    QString testMessage;
    QString commPort;

    // Tenta várias vezes abrir a conexão com a placa
    for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
        if (psController->openBoardConnection(boardId)) { // Abre a conexão com a placa
            commPort = psController->getBoardCommPort(boardId);
            testMessage = commPort + ":" + CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT;
            addCmdTestMessage(testId, boardId, testMessage, false);

            if (startTestExecution(testId, boardId)) { // Inicia a execução do teste

                // Verifica o tipo de teste a ser executado
                switch (testId) {
                case JigaTestInterface::CAN_INIT_TEST:
                case JigaTestInterface::MCU_RST_ACT_TEST:
                case JigaTestInterface::MCU_RST_DAC_TEST:
                case JigaTestInterface::MCU_RST_ATT_TEST:
                case JigaTestInterface::COMMUNICATION_TEST:
                case JigaTestInterface::MCU_IDENT_PORT_TEST:
                case JigaTestInterface::MCU_SEL_CANBUS1_TEST:
                case JigaTestInterface::MCU_SEL_CANBUS2_TEST:
                case JigaTestInterface::MCU_TOG_ECU3BUS_TEST:
                case JigaTestInterface::MCU_TOG_ECU4BUS_TEST:
                    testMessage = commPort + ":" + CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT;
                    addCmdTestMessage(testId, boardId, testMessage, false);
                    psController->closeBoardConnection(boardId);

                    // Ações específicas para alguns testes
                    switch (testId) {
                    case JigaTestInterface::MCU_RST_ATT_TEST :
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::MCU_RST_ATT_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;

                    case JigaTestInterface::MCU_SEL_CANBUS1_TEST:
                        Ecu3Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_1);
                        Ecu4Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_1);
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::MCU_SEL_CANBUS1_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestInterface::MCU_SEL_CANBUS2_TEST:
                        Ecu3Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_2);
                        Ecu4Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_2);
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::MCU_SEL_CANBUS2_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestInterface::MCU_TOG_ECU3BUS_TEST:
                        Ecu3Board::getInstance()->toggleCanBus();
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::MCU_TOG_ECU3BUS_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestInterface::MCU_TOG_ECU4BUS_TEST:
                        Ecu4Board::getInstance()->toggleCanBus();
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::MCU_TOG_ECU4BUS_ITEST, JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;
                    default:
                        break;
                    }
                    break;

                default:
                    // Inicia a monitorização dos resultados do teste
                    repController->startTestResultMonitor(testId, boardId);
                }
                return true;

            } else {
                // Mensagem de erro ao iniciar o teste
                testMessage = commPort + ": " + CmdMessageConstants::MSG_ERR_START_TEST ;
                addCmdTestMessage(testId, boardId, testMessage, false);
            }
            psController->closeBoardConnection(boardId);
        } else {
            // Mensagens de erro ao abrir a conexão com a porta
            testMessage = CmdMessageConstants::MSG_ERROR_TO_OPEN_PORT;
            addCmdTestMessage(testId, boardId, testMessage, true);

            testMessage = QString("%1 (%2)").arg(CmdMessageConstants::MSG_TRY_CONNECTION_AGAIN).arg(i + 1);
            addCmdTestMessage(testId, boardId, testMessage, true);
            QThread::sleep(1000);  // Atraso sincronizado, não recomendado na UI thread
        }
    }

    return false;
}

// Carrega a placa especificada e a prepara para o teste
int EcuBusinessController::loadBoard(int testId, int boardId) {
    QString commPort;
    QString testMessage;
    QString recvStr;
    bool portOpened;
    bool endOfLine = true;
    int retVal = -1;
    qDebug() << "Chamando loadSerialCommPorts...";

    int numberOfPorts = psController->loadSerialCommPorts();  // Carrega as portas seriais disponíveis

    qDebug() << "Número de portas disponíveis:" << numberOfPorts;

        // Verifica se há portas seriais disponíveis
        if (numberOfPorts <= 0) {
        qDebug() << "Erro: Nenhuma porta encontrada!";
        return ErrorCodeInterface::ERR_PORT_NOT_FOUND;  // Retorna erro de porta não encontrada
    }

    // Tenta abrir conexão com a placa várias vezes
    for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
        portOpened = psController->openBoardConnection(boardId);  // Tenta abrir a conexão da placa
        for (int j = 0; j < numberOfPorts; j++) {
            qDebug() << "Tentativa" << i+1 << "Porta" << j;
            qDebug() << "Porta aberta:" << portOpened;

            // Verifica se a porta foi aberta com sucesso
            if (portOpened) {
                psController->serialWrite(j, AtCommandConstants::AT_BI_CMD, endOfLine);  // Envia comando AT
                QThread::msleep(10);  // Aguarda 10 milissegundos
                recvStr = psController->serialBoardRead(boardId);  // Lê a resposta da placa
                qDebug() << "Resposta recebida:" << recvStr;

                // Verifica a resposta da placa com base no ID da placa
                switch (boardId) {
                case JigaTestInterface::ECU1_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU1_OK) {
                        commPort = Ecu1Board::getInstance()->getSerialCommPort().getDescriptivePortName();
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU1");
                        addCmdTestMessage(testId, boardId, testMessage, true);
                        psController->closeConnection(boardId);  // Fecha a conexão da placa
                        return ErrorCodeInterface::SUCCESS;  // Retorna sucesso
                    } else if (recvStr.toUpper() == AtCommandConstants::AT_ECU1_ERR) {
                        retVal = ErrorCodeInterface::ERR_BOARD_NOT_ACK;  // Erro de placa não reconhecida
                        break;
                    }
                    break;
                case JigaTestInterface::ECU2_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU2_OK) {
                        commPort = Ecu2Board::getInstance()->getSerialCommPort().getDescriptivePortName();
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU2");
                        addCmdTestMessage(testId, boardId, testMessage, true);
                        psController->closeConnection(boardId);
                        return ErrorCodeInterface::SUCCESS;
                    } else if (recvStr.toUpper() == AtCommandConstants::AT_ECU2_ERR) {
                        retVal = ErrorCodeInterface::ERR_BOARD_NOT_ACK;
                        break;
                    }
                    break;
                case JigaTestInterface::ECU3_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU3_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU3");
                        addCmdTestMessage(testId, boardId, testMessage, true);
                        psController->closeConnection(boardId);
                        return ErrorCodeInterface::SUCCESS;
                    } else if (recvStr.toUpper() == AtCommandConstants::AT_ECU3_ERR) {
                        retVal = ErrorCodeInterface::ERR_BOARD_NOT_ACK;
                        break;
                    }
                    break;
                case JigaTestInterface::ECU4_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU4_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU4");
                        addCmdTestMessage(testId, boardId, testMessage, true);
                        psController->closeConnection(boardId);
                        return ErrorCodeInterface::SUCCESS;
                    } else if (recvStr.toUpper() == AtCommandConstants::AT_ECU4_ERR) {
                        retVal = ErrorCodeInterface::ERR_BOARD_NOT_ACK;
                        break;
                    }
                    break;
                case JigaTestInterface::MCU1_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_MCU1_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "MCU1");
                        qDebug() << "Mensagem de teste:" << testMessage;
                        addCmdTestMessage(testId, boardId, testMessage, true);
                        psController->closeConnection(boardId);
                        return ErrorCodeInterface::SUCCESS;
                    } else if (recvStr.toUpper() == AtCommandConstants::AT_MCU1_ERR) {
                        retVal = ErrorCodeInterface::ERR_BOARD_NOT_ACK;
                        break;
                    }
                    break;
                default:
                    qDebug() << "Erro: ID da placa não reconhecido!" << boardId;
                            retVal = ErrorCodeInterface::ERR_BOARD_NOT_ACK;  // Erro de placa não reconhecida
                    break;
                }
                psController->closeConnection(boardId);  // Fecha a conexão da placa
            } else {
                qDebug() << "Erro: Porta" << j << "não pôde ser aberta!";
                retVal = ErrorCodeInterface::ERR_PORT_NOT_OPPENED;  // Erro de porta não aberta
            }
        }
    }

    qDebug() << "Retornando valor:" << retVal;
    return retVal;  // Retorna o valor final (sucesso ou erro)
}

// Carrega todas as placas disponíveis e retorna o número de placas carregadas com sucesso
int EcuBusinessController::loadAllBoards(int testId) {
    int numberOfBoards = 0;

    if (loadBoard(testId, JigaTestInterface::ECU1_BOARD_ID) == ErrorCodeInterface::SUCCESS) {
        numberOfBoards++;
    }
    if (loadBoard(testId, JigaTestInterface::ECU2_BOARD_ID) == ErrorCodeInterface::SUCCESS) {
        numberOfBoards++;
    }
    if (loadBoard(testId, JigaTestInterface::ECU3_BOARD_ID) == ErrorCodeInterface::SUCCESS) {
        numberOfBoards++;
    }
    if (loadBoard(testId, JigaTestInterface::ECU4_BOARD_ID) == ErrorCodeInterface::SUCCESS) {
        numberOfBoards++;
    }
    if (loadBoard(testId, JigaTestInterface::MCU1_BOARD_ID) == ErrorCodeInterface::SUCCESS) {
        numberOfBoards++;
    }
    return numberOfBoards;
}

// Carrega a porta de comunicação serial para uma placa específica
bool EcuBusinessController::loadSerialCommPort(int boardId) {
    int numberOfPorts, portFounds;

    // 1- Obtém o número total de portas disponíveis
    numberOfPorts = psController->getTotalNumberOfPorts();

    // 2- Verifica se pelo menos uma porta foi encontrada
    if (numberOfPorts <= 0) {
        return false;
    }

    // 3- Carrega as portas seriais disponíveis
    portFounds = psController->loadSerialCommPorts();

    // 4- Verifica se a porta de comunicação da placa foi encontrada
    if (portFounds > 0) {
        for (const Board* boardInfo : boardList) {
            if (boardInfo->getBoardIdentification() == boardId) {
                if (boardInfo->getSerialCommPort().getCommPortId() != ErrorCodeInterface::ERR_INVALID_PORT) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Carrega todas as portas de comunicação serial e retorna o número de portas carregadas
int EcuBusinessController::loadSerialCommPorts() {
    int numberOfPorts = 0;

    if (loadSerialCommPort(JigaTestInterface::ECU1_BOARD_ID)) {
        numberOfPorts++;
    }
    if (loadSerialCommPort(JigaTestInterface::ECU2_BOARD_ID)) {
        numberOfPorts++;
    }
    if (loadSerialCommPort(JigaTestInterface::ECU3_BOARD_ID)) {
        numberOfPorts++;
    }
    if (loadSerialCommPort(JigaTestInterface::ECU4_BOARD_ID)) {
        numberOfPorts++;
    }
    if (loadSerialCommPort(JigaTestInterface::MCU1_BOARD_ID)) {
        numberOfPorts++;
    }

    return numberOfPorts;
}

// Inicia a execução do teste na placa especificada
bool EcuBusinessController::startTestExecution(int testId, int boardId) {
    QString testMessage;
    bool endOfLine = true;

    QString commPort = psController->getBoardCommPort(boardId);
    // Define a mensagem inicial
    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + CmdMessageConstants::MSG_SEND_AT_COMMAND;
    addCmdTestMessage(testId, boardId, testMessage, false);

    // Define o comando com base no ID do teste
    QString command;
    switch (testId) {
    case JigaTestInterface::COMMUNICATION_TEST:
    case JigaTestInterface::MCU_IDENT_PORT_TEST:
        command = AtCommandConstants::AT_BI_CMD;
        break;
    case JigaTestInterface::DIGITAL_INPUT_TEST:
        command = AtCommandConstants::AT_DI_CMD;
        break;
    case JigaTestInterface::ANALOG_INPUT_TEST:
        command = AtCommandConstants::AT_AI_CMD;
        break;
    case JigaTestInterface::ANALOG_OUTPUT_TEST:
        command = AtCommandConstants::AT_AO_CMD;
        break;
    case JigaTestInterface::CAN_INIT_TEST:
        command = AtCommandConstants::AT_CS_CMD;
        break;
    case JigaTestInterface::CAN_LOOPBACK_TEST:
        command = AtCommandConstants::AT_CL_CMD;
        break;
    case JigaTestInterface::CAN1_NETWORK_TEST:
    case JigaTestInterface::MCU_SEL_CANBUS1_TEST:
        command = AtCommandConstants::AT_C1_CMD;
        break;
    case JigaTestInterface::CAN2_NETWORK_TEST:
    case JigaTestInterface::MCU_SEL_CANBUS2_TEST:
        command = AtCommandConstants::AT_C2_CMD;
        break;
    case JigaTestInterface::LIN_NETWORK_TEST:
        command = AtCommandConstants::AT_LN_CMD;
        break;
    case JigaTestInterface::MCU_RST_ACT_TEST:
        command = AtCommandConstants::AT_RU_CMD;
        break;
    case JigaTestInterface::MCU_RST_DAC_TEST:
        command = AtCommandConstants::AT_RD_CMD;
        break;
    case JigaTestInterface::MCU_RST_ATT_TEST:
        command = AtCommandConstants::AT_RT_CMD;
        break;
    case JigaTestInterface::MCU_GET_CANBUS_TEST:
        command = AtCommandConstants::AT_SB_CMD;
        break;
    case JigaTestInterface::MCU_TOG_ECU3BUS_TEST:
        command = AtCommandConstants::AT_SU_CMD;
        break;
    case JigaTestInterface::MCU_TOG_ECU4BUS_TEST:
        command = AtCommandConstants::AT_SD_CMD;
        break;
    }

    // Envia o comando
    psController->serialBoardWrite(boardId, command, endOfLine);
    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + command;
    addCmdTestMessage(testId, boardId, testMessage, false);

    // Verifica a execução do comando
    return acknowledgeAtCommand(testId, boardId);
}

// Define o controlador de relatórios para monitorar os testes
void EcuBusinessController::setReportController(RepBusinessController *rpController) {
    this->repController = rpController;
}

// Faz upload do firmware para a placa especificada
int EcuBusinessController::uploadFirmware(int boardId, int processorId) {
    QString appHexFile, avrdudeEXE, avrdudeCONF;
    QString optPROG, optBOOT1;
    QString cmdAppUpHEX, cmdBaudRate;
    int retVal;

    // Obtém o caminho do arquivo hex
    appHexFile = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY) + SystemProperties::getProperty(SystemProperties::ECU_DIRECTORY);

    // Define o arquivo hex específico para a placa
    switch (boardId) {
    case JigaTestInterface::ECU1_BOARD_ID:
        appHexFile += SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "1";
        break;
    case JigaTestInterface::ECU2_BOARD_ID:
        appHexFile += SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "2";
        break;
    case JigaTestInterface::ECU3_BOARD_ID:
        appHexFile += SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "3";
        break;
    case JigaTestInterface::ECU4_BOARD_ID:
        appHexFile += SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "4";
        break;
    default:
        return 1;
    }

    // Seleciona a taxa de baudrate de acordo com o processador
    switch (processorId) {
    case JigaTestInterface::ECU_OLD_BOOTLOADER:
        cmdBaudRate = SystemProperties::getProperty(SystemProperties::ECU_OLD_PROG_BAUDRATE);
        break;
    case JigaTestInterface::ECU_NEW_BOOTLOADER:
        cmdBaudRate = SystemProperties::getProperty(SystemProperties::ECU_NEW_PROG_BAUDRATE);
        break;
    }

    avrdudeEXE = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
                 + SystemProperties::getProperty(SystemProperties::AVRDUDE_PROGRAM);
    avrdudeCONF = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
                  + SystemProperties::getProperty(SystemProperties::AVRDUDE_CONFIG);

    optPROG = SystemProperties::getProperty(SystemProperties::ECU_OPT_PROG)
              + cmdBaudRate + " -P" + psController->getBoardCommPort(boardId);
    optBOOT1 = SystemProperties::getProperty(SystemProperties::MCU_OPT_BOOT1);

    // Constroi o comando para fazer upload do firmware
    cmdAppUpHEX = avrdudeEXE + " -C" + avrdudeCONF + " " + optPROG + " " + optBOOT1 + appHexFile + ":i";
    qDebug() << cmdAppUpHEX;

    // Faz o upload do firmware
    retVal = psController->writeFirmware(JigaTestInterface::ECU_FIRMWARE_UPLOAD, boardId, cmdAppUpHEX);

    return retVal;
}

// Obtém informações sobre as portas de comunicação serial
QVector<SerialCommPort*> EcuBusinessController::getSerialCommPortsInfo() {
    return psController->getSerialCommPortInfo();
}

// Encontra todas as portas de comunicação serial disponíveis e imprime informações
int EcuBusinessController::findSerialCommPorts() {
    QVector<SerialCommPort*> serialCommPorts = psController->findSerialCommPorts();

    if (!serialCommPorts.isEmpty()) {
        for (SerialCommPort* port : serialCommPorts) {
            if (port != nullptr) {
                port->printSerialCommPortInfo();
            }
        }
    }

    return JigaTestInterface::SUCCESS_EXECUTE_TEST;
}
