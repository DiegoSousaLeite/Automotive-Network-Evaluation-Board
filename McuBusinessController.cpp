#include "McuBusinessController.h"
#include <QDebug>

McuBusinessController::McuBusinessController(QObject *parent) :
    BusinessController(parent)
{
}

bool McuBusinessController::loadProgrammer(int programmerId) {
    switch (programmerId) {
    case JigaTestConstants::SERIAL_PROG_ID:
        return loadSerialProgrammer();
    case JigaTestConstants::USB_PROG_ID:
        return loadUsbProgrammer();
    default:
        return false;
    }
}

bool McuBusinessController::loadUsbProgrammer() {
    QString testMessage = tr(CmdMessageConstants::MSG_TRY_LOAD_PROGRAMMER);
    addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);

    bool retVal = psController->loadUsbProgrammer();

    // QTimer is used to handle the delay asynchronously
    QTimer::singleShot(1000, this, [this, retVal]() {
        QString testMessage;
        if (retVal) {
            testMessage = tr(CmdMessageConstants::MSG_SUCCESS_LOAD_PROGRAMMER);
        } else {
            testMessage = tr(CmdMessageConstants::MSG_NOT_FOUND_PROGRAMMER);
        }
        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);
    });

    return retVal;
}

bool McuBusinessController::loadSerialProgrammer() {
    int serialPorts = psController->getTotalNumberOfPorts();
    /*
     * QSettings settings("path/to/config.ini", QSettings::IniFormat);
     * int baudrate = settings.value(SystemProperties::MCU_PROG_BAUDRATE).toInt();
    */
    int baudrate = QSettings().value(SystemProperties::MCU_PROG_BAUDRATE).toInt();
    qDebug() << "baudrate: " << baudrate;

    if (serialPorts > 0) {
        for (int i = 0; i < serialPorts; i++) {
            bool retVal = psController->openConnection(i, baudrate);
            if (retVal) {
                QString commPort = psController->getSystemPortDescription(i);
                QString testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT);
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);
                qDebug() << testMessage;

                for (int j = 0; j < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; j++) {
                    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + tr(CmdMessageConstants::MSG_SEND_AT_COMMAND);
                    addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);
                    qDebug() << testMessage;
                    psController->serialWrite(i, AtCommandConstants::AT_CM_CMD, false);

                    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + AtCommandConstants::AT_CM_CMD;
                    qDebug() << testMessage;
                    addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);

                    QThread::msleep(500);
                    QString recvStr = psController->serialRead(i);

                    testMessage = commPort + ": " + recvStr;
                    addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);
                    qDebug() << testMessage;

                    if (recvStr == AtCommandConstants::AT_PROG_PM) {
                        psController->setBoardInformation(i, JigaTestConstants::MCU1_BOARD_ID);

                        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT) + "PROG";
                        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);
                        qDebug() << testMessage;

                        psController->closeConnection(i);
                        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);
                        qDebug() << testMessage;

                        return true;
                    }
                }
                psController->closeConnection(i);
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);
                qDebug() << testMessage;
            }
        }
    }
    return false;
}

int McuBusinessController::getSerialProgrammerMode() {
    QString recvStr;
    bool retVal;
    QString commPort;
    QString testMessage;

    // Abrindo conexão com a porta serial para o modo programador
    retVal = psController->openBoardConnection(JigaTestConstants::PROG_BOARD_ID, 19200);
    if (retVal) {
        commPort = psController->getBoardCommPort(JigaTestConstants::PROG_BOARD_ID);
        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT);
        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);

        // Verificando o modo do programador
        for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + tr(CmdMessageConstants::MSG_SEND_AT_COMMAND);
            addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);
            psController->serialBoardWrite(JigaTestConstants::PROG_BOARD_ID, AtCommandConstants::AT_CM_CMD, false);

            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + AtCommandConstants::AT_CM_CMD;
            addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);

            QThread::msleep(500);

            recvStr = psController->serialBoardRead(JigaTestConstants::PROG_BOARD_ID);

            testMessage = commPort + ": " + recvStr;
            addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);

            if (recvStr == AtCommandConstants::AT_PROG_SM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " serial!";
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestConstants::PROG_BOARD_ID);
                return JigaTestConstants::PROG_SERIAL_MODE;
            } else if (recvStr == AtCommandConstants::AT_PROG_PM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " de programação!";
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestConstants::PROG_BOARD_ID);
                return JigaTestConstants::PROG_PROGRAMMER_MODE;
            }
        }
        psController->closeBoardConnection(JigaTestConstants::PROG_BOARD_ID);
        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);
    }

    return JigaTestConstants::PROG_UNKNOWN_MODE;
}

void McuBusinessController::setSerialProgrammerMode(int progMode) {
    QString recvStr;
    bool retVal;
    QString commPort;
    QString testMessage;

    // Abre a conexão com o board especificado
    retVal = psController->openBoardConnection(JigaTestConstants::PROG_BOARD_ID, 19200);
    if (retVal) {
        commPort = psController->getBoardCommPort(JigaTestConstants::PROG_BOARD_ID);
        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT);
        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);

        // Configura o modo do programador
        for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + tr(CmdMessageConstants::MSG_SEND_AT_COMMAND);
            addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);

            QString cmd = (progMode == JigaTestConstants::PROG_SERIAL_MODE) ? AtCommandConstants::AT_SM_CMD : AtCommandConstants::AT_PM_CMD;
            psController->serialBoardWrite(JigaTestConstants::PROG_BOARD_ID, cmd, false);

            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + cmd;
            addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);

            QThread::msleep(500);

            // Leitura da resposta
            recvStr = psController->serialBoardRead(JigaTestConstants::PROG_BOARD_ID);
            testMessage = commPort + ": " + recvStr;
            addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);

            if (recvStr == AtCommandConstants::AT_PROG_SM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " serial!";
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestConstants::PROG_BOARD_ID);
                testMessage = commPort+": "+tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD,JigaTestConstants::PROG_BOARD_ID,testMessage,false);
                return;
            } else if (recvStr == AtCommandConstants::AT_PROG_PM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " de programação!";
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestConstants::PROG_BOARD_ID);
                testMessage = commPort+": "+tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD,JigaTestConstants::PROG_BOARD_ID,testMessage,false);
                return;
            }
        }
        psController->closeBoardConnection(JigaTestConstants::PROG_BOARD_ID);
    }
}

int McuBusinessController::uploadFirmware(int programmerId) {
    QString basePath = QDir(SystemProperties::USER_DIRECTORY).absolutePath();
    QDir mcuDir(basePath);
    mcuDir.cd(SystemProperties::MCU_DIRECTORY);

    QString appHexFile = mcuDir.filePath(SystemProperties::MCU_APPLICATION);
    QString bootHexFile = mcuDir.filePath(SystemProperties::MCU_BOOTLOADER);

    QDir avrDir(basePath);
    QString avrdudeExe = avrDir.filePath(SystemProperties::AVRDUDE_PROGRAM);
    QString avrdudeConf = avrDir.filePath(SystemProperties::AVRDUDE_CONFIG);


    QString optFUSE = tr(SystemProperties::MCU_OPT_FUSE);
    QString optBOOT1 = tr(SystemProperties::MCU_OPT_BOOT1);
    QString optBOOT2 = tr(SystemProperties::MCU_OPT_BOOT2);
    QString optPROG = tr(SystemProperties::MCU_OPT_PROG);

    switch (programmerId) {
    case JigaTestConstants::USB_PROG_ID:
        optPROG += tr(SystemProperties::MCU_PROG_USB);
        break;
    case JigaTestConstants::SERIAL_PROG_ID:
        optPROG += tr(SystemProperties::MCU_PROG_SERIAL) + " -b" + tr(SystemProperties::MCU_PROG_BAUDRATE) + " -P";
        break;
    default:
        return 1;
    }

    QString cmdBootUpFuse = avrdudeExe + " -C" + avrdudeConf + " " + optPROG + " " + optFUSE;
    QString cmdBootUpHEX = avrdudeExe + " -C" + avrdudeConf + " " + optPROG + " " + optBOOT1 + bootHexFile + ":i " + optBOOT2;
    QString cmdAppUpHEX = avrdudeExe + " -C" + avrdudeConf + " " + optPROG + " " + optBOOT1 + appHexFile + ":i";

    qDebug() << cmdBootUpFuse;
    qDebug() << cmdBootUpHEX;
    qDebug() << cmdAppUpHEX;

    int retVal = psController->writeFirmware(cmdBootUpFuse);
    if (retVal < 0) {
        qDebug() << "retVal =" << retVal;
        return retVal;
    }

    retVal = psController->writeFirmware(cmdBootUpHEX);
    if (retVal < 0) {
        qDebug() << "retVal =" << retVal;
        return retVal;
    }

    retVal = psController->writeFirmware(cmdAppUpHEX);
    return retVal;
}

bool McuBusinessController::setCanBus1Network() {
    bool retVal = false;
    int resVal;
    QString testMessage;
    int stateMachine;

    // 1 - Abrindo conexão com o programador
    retVal = psController->openBoardConnection(JigaTestConstants::MCU1_BOARD_ID, 19200);
    if (!retVal) {
        return false;
    }

    // 3 - Verificar configuração de rede CAN para ECU3 e ECU4
    resVal = checkCanBus1Network(JigaTestConstants::CAN1_NETWORK_TEST);
    switch (resVal) {
    case EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE:
        testMessage = tr(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + c1NetworkModel->getBoardDescription(JigaTestConstants::MCU1_BOARD_ID);
        addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID, testMessage, true);
        c1NetworkModel->setTestResult(JigaTestConstants::MCU1_BOARD_ID, JigaTestConstants::CAN1_NETWORK_TEST);
        return false;

    case JigaTestConstants::ECU_CANBUS_1:
        testMessage = tr("ECU3 and ECU4 connected on CANBUS1!");
        addCmdTestMessage(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID, testMessage, true);
        return true;

    default:
        stateMachine = McuBusinessInterface::SM_SEL_SL_STATE;
        for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
            // Configurar CAN bus
            switch (stateMachine) {
            case McuBusinessInterface::SM_SEL_SL_STATE:
                sendAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID, AtCommandConstants::AT_SL_CMD);
                retVal = acknowledgeAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID);
                if (retVal) {
                    if (resVal == JigaTestConstants::ECU_CANBUS_2) {
                        stateMachine = McuBusinessInterface::SM_SEL_UD_STATE;
                    } else if (resVal == JigaTestConstants::ECU3_CANBUS1) {
                        stateMachine = McuBusinessInterface::SM_SEL_SU_STATE;
                    } else if (resVal == JigaTestConstants::ECU4_CANBUS1) {
                        stateMachine = McuBusinessInterface::SM_SEL_SD_STATE;
                    }
                }
                break;
            case McuBusinessInterface::SM_SEL_UD_STATE:
                sendAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID, AtCommandConstants::AT_SU_CMD);
                retVal = acknowledgeAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID);
                if (retVal) stateMachine = McuBusinessInterface::SM_SEL_SD_STATE;
                break;
            case McuBusinessInterface::SM_SEL_SU_STATE:
                sendAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID, AtCommandConstants::AT_SU_CMD);
                retVal = acknowledgeAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID);
                if (retVal) stateMachine = McuBusinessInterface::SM_SEL_SV_STATE;
                break;
            case McuBusinessInterface::SM_SEL_SD_STATE:
                sendAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID, AtCommandConstants::AT_SD_CMD);
                retVal = acknowledgeAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID);
                if (retVal) stateMachine = McuBusinessInterface::SM_SEL_SV_STATE;
                break;
            case McuBusinessInterface::SM_SEL_SV_STATE:
                sendAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID, AtCommandConstants::AT_SD_CMD);
                retVal = acknowledgeAtCommand(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::MCU1_BOARD_ID);
                if (retVal) return true;
                break;
            }
        }
        break;
    }

    return false;
}

int McuBusinessController::checkCanBus1Network(int testId) {
    QString recvStr = "";
    QString testMessage;
    QString commPort;
    int code = -1;

    commPort = psController->getBoardCommPort(JigaTestConstants::MCU1_BOARD_ID);

    // 1 - Send AT command to MCU1
    for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
        testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + CmdMessageConstants::MSG_SEND_AT_COMMAND;
        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);

        psController->serialBoardWrite(JigaTestConstants::MCU1_BOARD_ID, AtCommandConstants::AT_SB_CMD, true);

        testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + AtCommandConstants::AT_SB_CMD;
        addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);

        // 2 - Waiting a while
        QThread::msleep(500);  // Delay in seconds

        // 3 - Getting test result
        recvStr = psController->serialBoardRead(JigaTestConstants::MCU1_BOARD_ID);
        testMessage = commPort + ": " + recvStr;
        addCmdTestMessage(testId, JigaTestConstants::MCU1_BOARD_ID, testMessage, false);

        // 4 - Checking returned code
        if (!recvStr.isEmpty()) {
            code = getTestReportCode(recvStr);
            if (code != EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE) {
                break;
            }
        }
    }

    return code;
}

bool McuBusinessController::setCanBus2Network() {
    // Implementação ainda não suportada.
    qWarning("setCanBus2Network not supported yet.");
    throw std::runtime_error("setCanBus2Network not supported yet.");
    return false;
}
