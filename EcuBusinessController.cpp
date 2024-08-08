#include "EcuBusinessController.h"
#include <QThread>
#include <QDebug>

EcuBusinessController::EcuBusinessController(QObject *parent)
    : BusinessController(parent), repController(nullptr){
    psController = new PersistenceController();

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

                    switch (testId) {
                    case JigaTestInterface::MCU_RST_ATT_TEST :
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID,JigaTestInterface::MCU_RST_ATT_ITEST,JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;

                    case JigaTestInterface::MCU_SEL_CANBUS1_TEST:
                        Ecu3Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_1);
                        Ecu4Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_1);
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID,JigaTestInterface::MCU_SEL_CANBUS1_ITEST,JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestInterface::MCU_SEL_CANBUS2_TEST:
                        Ecu3Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_2);
                        Ecu4Board::getInstance()->setCanbus(JigaTestInterface::ECU_CANBUS_2);
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID,JigaTestInterface::MCU_SEL_CANBUS2_ITEST,JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestInterface::MCU_TOG_ECU3BUS_TEST:
                        Ecu3Board::getInstance()->toggleCanBus();
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID,JigaTestInterface::MCU_TOG_ECU3BUS_ITEST,JigaTestInterface::SUCCESS_EXECUTE_TEST);
                        break;
                    case JigaTestInterface::MCU_TOG_ECU4BUS_TEST:
                        Ecu4Board::getInstance()->toggleCanBus();
                        mcu1InterModel->setIndividualTestResult(JigaTestInterface::MCU1_BOARD_ID,JigaTestInterface::MCU_TOG_ECU4BUS_ITEST,JigaTestInterface::SUCCESS_EXECUTE_TEST);
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
                    }else if(recvStr.toUpper() == AtCommandConstants::AT_ECU2_ERR){
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
                    }else if(recvStr.toUpper() == AtCommandConstants::AT_ECU3_ERR){
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
                    }else if(recvStr.toUpper() == AtCommandConstants::AT_ECU4_ERR){
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
                    }else if(recvStr.toUpper() == AtCommandConstants::AT_MCU1_ERR){
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


int EcuBusinessController::loadAllBoards(int testId)
{
    int numberOfBoards = 0;

    if(loadBoard(testId,JigaTestInterface::ECU1_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestInterface::ECU2_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestInterface::ECU3_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestInterface::ECU4_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestInterface::MCU1_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    return numberOfBoards;
}

bool EcuBusinessController::loadSerialCommPort(int boardId) {
    int numberOfPorts, portFounds;

    // 1-Getting number of ports
    numberOfPorts = psController->getTotalNumberOfPorts();

    // 2-Check if at least one port was found
    if (numberOfPorts <= 0) {
        return false;
    }

    // 3 - Load Serial Comm Ports
    portFounds = psController->loadSerialCommPorts();

    // 4 - Check if the board comm port was found
    if (portFounds > 0) {
        for (const Board* boardInfo : boardList) {
            if (boardInfo->getBoardIdentification() == boardId) {
                if (boardInfo->getSerialCommPort().getCommPortId() !=ErrorCodeInterface::ERR_INVALID_PORT) {
                    return true;
                }
            }
        }
    }

    return false;
}

int EcuBusinessController::loadSerialCommPorts()
{
    int numberOfPorts = 0;

    if(loadSerialCommPort(JigaTestInterface::ECU1_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestInterface::ECU2_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestInterface::ECU3_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestInterface::ECU4_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestInterface::MCU1_BOARD_ID)){
        numberOfPorts++;
    }

    return numberOfPorts;

}

bool EcuBusinessController::startTestExecution(int testId, int boardId) {
    QString testMessage;
    bool endOfLine = true;

    QString commPort = psController->getBoardCommPort(boardId);
    // Set initial message
    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + CmdMessageConstants::MSG_SEND_AT_COMMAND;
    addCmdTestMessage(testId, boardId, testMessage, false);

    // Define command based on testId
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

    // Send command
    psController->serialBoardWrite(boardId, command, endOfLine);
    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + command;
    addCmdTestMessage(testId, boardId, testMessage, false);

    // Verify the command execution
    return acknowledgeAtCommand(testId, boardId);
}

void EcuBusinessController::setReportController(RepBusinessController *rpController) {
    this->repController = rpController;
}

int EcuBusinessController::uploadFirmware(int boardId, int processorId)
{
    QString appHexFile, avrdudeEXE, avrdudeCONF;
    QString optPROG, optBOOT1;
    QString cmdAppUpHEX, cmdBaudRate;
    int retVal;

    // 2 - Printing board information
    appHexFile = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY) + SystemProperties::getProperty(SystemProperties::ECU_DIRECTORY);

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

    // 3 - Selecting baudrate according to processor
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

    // 4 - Building the command string
    cmdAppUpHEX = avrdudeEXE + " -C" + avrdudeCONF + " " + optPROG + " " + optBOOT1 + appHexFile + ":i";
    qDebug() << cmdAppUpHEX;

    // 5 - Upload firmware
    retVal = psController->writeFirmware(JigaTestInterface::ECU_FIRMWARE_UPLOAD, boardId, cmdAppUpHEX);

    return retVal;
}

//int EcuBusinessController::uploadFirmware(int boardId) {
//    QString appHexFile, avrdudeEXE, avrdudeCONF;
//    QString optPROG, optBOOT1;
//    QString cmdAppUpHEX;
//    int retVal;

//    // 2 - printing board information
//    appHexFile = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
//                 + SystemProperties::getProperty(SystemProperties::ECU_DIRECTORY);

//    switch (boardId) {
//    case JigaTestInterface::ECU1_BOARD_ID: {
//        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "1";
//        break;
//    }
//    case JigaTestInterface::ECU2_BOARD_ID: {
//        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "2";
//        break;
//    }
//    case JigaTestInterface::ECU3_BOARD_ID: {
//        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "3";
//        break;
//    }
//    case JigaTestInterface::ECU4_BOARD_ID: {
//        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "4";
//        break;
//    }
//    default: {
//        return 1;
//    }
//    }

//    avrdudeEXE = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
//                 + SystemProperties::getProperty(SystemProperties::AVRDUDE_PROGRAM);
//    avrdudeCONF = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
//                  + SystemProperties::getProperty(SystemProperties::AVRDUDE_CONFIG);

//    optPROG = SystemProperties::getProperty(SystemProperties::ECU_OPT_PROG)
//              + SystemProperties::getProperty(SystemProperties::ECU_PROG_BAUDRATE)
//              + " -P" + psController->getBoardCommPort(boardId);
//    optBOOT1 = SystemProperties::getProperty(SystemProperties::MCU_OPT_BOOT1);

//    // 2 - Building the command string
//    cmdAppUpHEX = QString("%1 -C %2 %3 %4 %5:i")
//                      .arg(avrdudeEXE, avrdudeCONF, optPROG, optBOOT1, appHexFile);
//    qDebug() << cmdAppUpHEX;

//    // Upgrading firmware
//    retVal = psController->writeFirmware(cmdAppUpHEX);

//    return retVal;
//}

//int EcuBusinessController::uploadFirmware(int portId, const QString &pathToHexFile) {
//    if (!QFile::exists(pathToHexFile)) {
//        qDebug() << "Invalid path to hex file:" << pathToHexFile;
//        return -1;
//    }

//    QString userDir = QDir::homePath();
//    QString avrdudeExe = userDir + "/avrdude"; // Adjust the path as necessary
//    QString avrdudeConf = userDir + "/avrdude.conf"; // Adjust the path as necessary

//    QString portDesc = psController->getSystemPortDescription(portId);
//    QString optProg = "-cstk500v1 -b19200 -P" + portDesc; // Example programmer options
//    QString optBoot1 = "-U flash:w:";

//    QString cmdAppUpHex = QString("%1 -C %2 %3 %4%5:i").arg(avrdudeExe, avrdudeConf, optProg, optBoot1, pathToHexFile);
//    qDebug() << "Command to execute:" << cmdAppUpHex;

//    QProcess process;
//    process.start(cmdAppUpHex);
//    if (!process.waitForFinished()) {
//        qDebug() << "Error executing avrdude:" << process.errorString();
//        return -1;
//    }

//    return process.exitCode(); // Return the exit code from avrdude
//}

QVector<SerialCommPort*> EcuBusinessController::getSerialCommPortsInfo() {
    return psController->getSerialCommPortInfo();
}

int EcuBusinessController::findSerialCommPorts()
{
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
