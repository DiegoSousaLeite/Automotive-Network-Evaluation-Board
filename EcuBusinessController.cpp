#include "EcuBusinessController.h"
#include <QThread>
#include <QDebug>

EcuBusinessController::EcuBusinessController(QObject *parent)
    : BusinessController(parent), repController(nullptr){

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
    QString commPort;
    QString testMessage;
    QString recvStr;
    bool portOpened;
    bool endOfLine = true;
    int retVal = 0;
    int baudrate = (boardId == JigaTestConstants::MCU1_BOARD_ID) ? QString(SystemProperties::MCU_APP_BAUDRATE).toInt() : QString(SystemProperties::ECU_APP_BAUDRATE).toInt();
    int numberOfPorts = QSerialPortInfo::availablePorts().count();

    if (numberOfPorts <= 0) {
        return ErrorCodeInterface::ERR_PORT_NOT_FOUND;
    }

    for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
        for (int j = 0; j < numberOfPorts; j++) {
            portOpened = psController->openBoardConnection(j, baudrate);
            if(portOpened == true){
                psController->serialWrite(j, AtCommandConstants::AT_BI_CMD, endOfLine);
                QThread::msleep(10);
                recvStr = psController->serialRead(j);

                switch (boardId) {
                case JigaTestConstants::ECU1_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU1_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU1");
                        psController->setBoardInformation(j, boardId);
                        psController->closeConnection(j);
                        return ErrorCodeInterface::SUCCESS;
                    }
                    break;
                case JigaTestConstants::ECU2_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU2_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU2");
                        addCmdTestMessage(testId, boardId, testMessage, false);
                        psController->setBoardInformation(j, boardId);
                        psController->closeConnection(j);
                        return ErrorCodeInterface::SUCCESS;
                    }
                    break;
                case JigaTestConstants::ECU3_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU3_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU3");
                        addCmdTestMessage(testId, boardId, testMessage, false);
                        psController->setBoardInformation(j, boardId);
                        psController->closeConnection(j);
                        return ErrorCodeInterface::SUCCESS;
                    }
                    break;
                case JigaTestConstants::ECU4_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_ECU4_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "ECU4");
                        addCmdTestMessage(testId, boardId, testMessage, false);
                        psController->setBoardInformation(j, boardId);
                        psController->closeConnection(j);
                        return ErrorCodeInterface::SUCCESS;
                    }
                    break;
                case JigaTestConstants::MCU1_BOARD_ID:
                    if (recvStr.toUpper() == AtCommandConstants::AT_MCU1_OK) {
                        commPort = psController->getSystemPortDescription(j);
                        testMessage = QString("%1: %2%3").arg(commPort, CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT, "MCU1");
                        addCmdTestMessage(testId, boardId, testMessage, false);
                        psController->setBoardInformation(j, boardId);
                        psController->closeConnection(j);
                        return ErrorCodeInterface::SUCCESS;
                    }
                    break;
                default:
                    retVal = ErrorCodeInterface::ERR_BOARD_NOT_ACK;
                    break;
                }
                psController->closeConnection(j);
            } else {
                retVal = ErrorCodeInterface::ERR_PORT_NOT_OPPENED;
            }
        }
    }

    return retVal;
}

int EcuBusinessController::loadAllBoards(int testId)
{
    int numberOfBoards = 0;

    if(loadBoard(testId,JigaTestConstants::ECU1_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestConstants::ECU2_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestConstants::ECU3_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestConstants::ECU4_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    if(loadBoard(testId,JigaTestConstants::MCU1_BOARD_ID)==ErrorCodeInterface::SUCCESS){
        numberOfBoards++;
    }
    return numberOfBoards;
}

bool EcuBusinessController::loadSerialCommPort(int boardId) {

    int numberOfPorts = psController->getTotalNumberOfPorts();
    if (numberOfPorts <= 0) {
        return false;
    }

    QString recvStr;
    QString portDesc;
    //QString descPortName;

    // Definindo descrições baseadas no id da placa
    switch (boardId) {
    case JigaTestConstants::ECU1_BOARD_ID:
    case JigaTestConstants::ECU2_BOARD_ID:
    case JigaTestConstants::ECU3_BOARD_ID:
    case JigaTestConstants::ECU4_BOARD_ID:
        portDesc = SystemProperties::getPortDescription(boardId) + QString::number(boardId);
        //descPortName = SystemProperties::ECU_DESC_PORT_NAME;
        break;
    case JigaTestConstants::MCU1_BOARD_ID:
        portDesc = SystemProperties::getPortDescription(boardId);
        //descPortName = SystemProperties::MCU_DESC_PORT_NAME;
        break;
    }

    // Verificando as descrições das portas
    for (int i = 0; i < numberOfPorts; i++) {
        for (int j = 0; j < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; j++) {
            recvStr = psController->getPortDescription(i);

            if(!(recvStr.toLower() == portDesc.toLower())){
            }else{
                switch(boardId){
                case JigaTestConstants::ECU1_BOARD_ID:
                    psController->setBoardInformation(i, JigaTestConstants::ECU1_BOARD_ID);
                    return true;
                case JigaTestConstants::ECU2_BOARD_ID:
                    psController->setBoardInformation(i, JigaTestConstants::ECU2_BOARD_ID);
                    return true;
                case JigaTestConstants::ECU3_BOARD_ID:
                    psController->setBoardInformation(i, JigaTestConstants::ECU3_BOARD_ID);
                    return true;
                case JigaTestConstants::ECU4_BOARD_ID:
                    psController->setBoardInformation(i, JigaTestConstants::ECU4_BOARD_ID);
                    return true;
                case JigaTestConstants::MCU1_BOARD_ID:
                    psController->setBoardInformation(i, JigaTestConstants::MCU1_BOARD_ID);
                    return true;
                default:
                    break;
                }
            }
        }
    }
    return false;
}

int EcuBusinessController::loadAllSerialCommPorts()
{
    int numberOfPorts = 0;

    if(loadSerialCommPort(JigaTestConstants::ECU1_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestConstants::ECU2_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestConstants::ECU3_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestConstants::ECU4_BOARD_ID)){
        numberOfPorts++;
    }
    if(loadSerialCommPort(JigaTestConstants::MCU1_BOARD_ID)){
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
    case JigaTestConstants::COMMUNICATION_TEST:
    case JigaTestConstants::MCU_IDENT_PORT_TEST:
        command = AtCommandConstants::AT_BI_CMD;
        break;
    case JigaTestConstants::DIGITAL_INPUT_TEST:
        command = AtCommandConstants::AT_DI_CMD;
        break;
    case JigaTestConstants::ANALOG_INPUT_TEST:
        command = AtCommandConstants::AT_AI_CMD;
        break;
    case JigaTestConstants::ANALOG_OUTPUT_TEST:
        command = AtCommandConstants::AT_AO_CMD;
        break;
    case JigaTestConstants::CAN_INIT_TEST:
        command = AtCommandConstants::AT_CS_CMD;
        break;
    case JigaTestConstants::LOOPBACK_CAN_TEST:
        command = AtCommandConstants::AT_CL_CMD;
        break;
    case JigaTestConstants::CAN1_NETWORK_TEST:
    case JigaTestConstants::MCU_SEL_CANBUS1_TEST:
        command = AtCommandConstants::AT_C1_CMD;
        break;
    case JigaTestConstants::CAN2_NETWORK_TEST:
    case JigaTestConstants::MCU_SEL_CANBUS2_TEST:
        command = AtCommandConstants::AT_C2_CMD;
        break;
    case JigaTestConstants::LIN_NETWORK_TEST:
        command = AtCommandConstants::AT_LN_CMD;
        break;
    case JigaTestConstants::MCU_RST_ACT_TEST:
        command = AtCommandConstants::AT_RU_CMD;
        break;
    case JigaTestConstants::MCU_RST_DAC_TEST:
        command = AtCommandConstants::AT_RD_CMD;
        break;
    case JigaTestConstants::MCU_RST_ATT_TEST:
        command = AtCommandConstants::AT_RT_CMD;
        break;
    case JigaTestConstants::MCU_GET_CANBUS_TEST:
        command = AtCommandConstants::AT_SB_CMD;
        break;
    case JigaTestConstants::MCU_TOG_ECU3BUS_TEST:
        command = AtCommandConstants::AT_SU_CMD;
        break;
    case JigaTestConstants::MCU_TOG_ECU4BUS_TEST:
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

int EcuBusinessController::uploadFirmware(int boardId) {
    QString appHexFile, avrdudeEXE, avrdudeCONF;
    QString optPROG, optBOOT1;
    QString cmdAppUpHEX;
    int retVal;

    // 2 - printing board information
    appHexFile = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
                 + SystemProperties::getProperty(SystemProperties::ECU_DIRECTORY);

    switch (boardId) {
    case JigaTestConstants::ECU1_BOARD_ID: {
        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "1";
        break;
    }
    case JigaTestConstants::ECU2_BOARD_ID: {
        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "2";
        break;
    }
    case JigaTestConstants::ECU3_BOARD_ID: {
        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "3";
        break;
    }
    case JigaTestConstants::ECU4_BOARD_ID: {
        appHexFile = SystemProperties::getProperty(SystemProperties::ECU_APPLICATION) + "4";
        break;
    }
    default: {
        return 1;
    }
    }

    avrdudeEXE = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
                 + SystemProperties::getProperty(SystemProperties::AVRDUDE_PROGRAM);
    avrdudeCONF = SystemProperties::getProperty(SystemProperties::USER_DIRECTORY)
                  + SystemProperties::getProperty(SystemProperties::AVRDUDE_CONFIG);

    optPROG = SystemProperties::getProperty(SystemProperties::ECU_OPT_PROG)
              + SystemProperties::getProperty(SystemProperties::ECU_PROG_BAUDRATE)
              + " -P" + psController->getBoardCommPort(boardId);
    optBOOT1 = SystemProperties::getProperty(SystemProperties::MCU_OPT_BOOT1);

    // 2 - Building the command string
    cmdAppUpHEX = QString("%1 -C %2 %3 %4 %5:i")
                      .arg(avrdudeEXE, avrdudeCONF, optPROG, optBOOT1, appHexFile);
    qDebug() << cmdAppUpHEX;

    // Upgrading firmware
    retVal = psController->writeFirmware(cmdAppUpHEX);

    return retVal;
}

int EcuBusinessController::uploadFirmware(int portId, const QString &pathToHexFile) {
    if (!QFile::exists(pathToHexFile)) {
        qDebug() << "Invalid path to hex file:" << pathToHexFile;
        return -1;
    }

    QString userDir = QDir::homePath();
    QString avrdudeExe = userDir + "/avrdude"; // Adjust the path as necessary
    QString avrdudeConf = userDir + "/avrdude.conf"; // Adjust the path as necessary

    QString portDesc = psController->getSystemPortDescription(portId);
    QString optProg = "-cstk500v1 -b19200 -P" + portDesc; // Example programmer options
    QString optBoot1 = "-U flash:w:";

    QString cmdAppUpHex = QString("%1 -C %2 %3 %4%5:i").arg(avrdudeExe, avrdudeConf, optProg, optBoot1, pathToHexFile);
    qDebug() << "Command to execute:" << cmdAppUpHex;

    QProcess process;
    process.start(cmdAppUpHex);
    if (!process.waitForFinished()) {
        qDebug() << "Error executing avrdude:" << process.errorString();
        return -1;
    }

    return process.exitCode(); // Return the exit code from avrdude
}

QVector<SerialCommPort*> EcuBusinessController::getSerialCommPortsInfo() {
    return psController->getSerialCommPortInfo();
}
