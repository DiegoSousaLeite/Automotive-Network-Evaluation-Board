#include "McuBusinessController.h"
#include <QDebug>

McuBusinessController::McuBusinessController(QObject *parent) :
    BusinessController(parent)
{
    // Construtor padrão inicializa o BusinessController com o pai especificado.
}

bool McuBusinessController::loadProgrammer(int programmerId) {
    // Carrega o programador com base no ID fornecido.
    // Retorna true se o carregamento foi bem-sucedido, caso contrário, false.
    switch (programmerId) {
    case JigaTestInterface::SERIAL_PROG_ID:
        return loadSerialProgrammer();
    case JigaTestInterface::USB_PROG_ID:
        return loadUsbProgrammer();
    default:
        return false;
    }
}

bool McuBusinessController::loadUsbProgrammer() {
    // Tenta carregar um programador USB.
    QString testMessage = tr(CmdMessageConstants::MSG_TRY_LOAD_PROGRAMMER);
    addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);

    bool retVal = psController->loadUsbProgrammer();

    // Usando QTimer para lidar com o atraso de forma assíncrona.
    QTimer::singleShot(1000, this, [this, retVal]() {
        QString testMessage;
        if (retVal) {
            testMessage = tr(CmdMessageConstants::MSG_SUCCESS_LOAD_PROGRAMMER);
        } else {
            testMessage = tr(CmdMessageConstants::MSG_NOT_FOUND_PROGRAMMER);
        }
        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);
    });

    return retVal;
}

bool McuBusinessController::loadSerialProgrammer() {
    // Carrega um programador serial.
    int serialPorts = psController->getTotalNumberOfPorts();
    int baudrate = QSettings().value(SystemProperties::MCU_PROG_BAUDRATE).toInt();
    qDebug() << "baudrate: " << baudrate;

    if (serialPorts > 0) {
        for (int i = 0; i < serialPorts; i++) {
            bool retVal = psController->openConnection(i, baudrate);
            if (retVal) {
                QString commPort = psController->getSystemPortDescription(i);
                QString testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT);
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);
                qDebug() << testMessage;

                for (int j = 0; j < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; j++) {
                    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + tr(CmdMessageConstants::MSG_SEND_AT_COMMAND);
                    addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);
                    qDebug() << testMessage;
                    psController->serialWrite(i, AtCommandConstants::AT_CM_CMD, false);

                    testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + AtCommandConstants::AT_CM_CMD;
                    qDebug() << testMessage;
                    addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);

                    QThread::msleep(500);
                    QString recvStr = psController->serialRead(i);

                    testMessage = commPort + ": " + recvStr;
                    addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);
                    qDebug() << testMessage;

                    if (recvStr == AtCommandConstants::AT_PROG_PM) {
                        psController->setBoardInformation(i, JigaTestInterface::MCU1_BOARD_ID);

                        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_BOARD_ON_SERIAL_PORT) + "PROG";
                        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);
                        qDebug() << testMessage;

                        psController->closeConnection(i);
                        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);
                        qDebug() << testMessage;

                        return true;
                    }
                }
                psController->closeConnection(i);
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);
                qDebug() << testMessage;
            }
        }
    }
    return false;
}

int McuBusinessController::getSerialProgrammerMode() {
    // Obtém o modo do programador serial atual.
    QString recvStr;
    bool retVal;
    QString commPort;
    QString testMessage;

    retVal = psController->openBoardConnection(JigaTestInterface::PROG_BOARD_ID, 19200);
    if (retVal) {
        commPort = psController->getBoardCommPort(JigaTestInterface::PROG_BOARD_ID);
        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT);
        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);

        for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + tr(CmdMessageConstants::MSG_SEND_AT_COMMAND);
            addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);
            psController->serialBoardWrite(JigaTestInterface::PROG_BOARD_ID, AtCommandConstants::AT_CM_CMD, false);

            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + AtCommandConstants::AT_CM_CMD;
            addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);

            QThread::msleep(500);

            recvStr = psController->serialBoardRead(JigaTestInterface::PROG_BOARD_ID);

            testMessage = commPort + ": " + recvStr;
            addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);

            if (recvStr == AtCommandConstants::AT_PROG_SM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " serial!";
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestInterface::PROG_BOARD_ID);
                return JigaTestInterface::PROG_SERIAL_MODE;
            } else if (recvStr == AtCommandConstants::AT_PROG_PM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " de programação!";
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestInterface::PROG_BOARD_ID);
                return JigaTestInterface::PROG_PROGRAMMER_MODE;
            }
        }
        psController->closeBoardConnection(JigaTestInterface::PROG_BOARD_ID);
        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);
    }

    return JigaTestInterface::PROG_UNKNOWN_MODE;
}

void McuBusinessController::setSerialProgrammerMode(int progMode) {
    // Define o modo do programador serial.
    QString recvStr;
    bool retVal;
    QString commPort;
    QString testMessage;

    retVal = psController->openBoardConnection(JigaTestInterface::PROG_BOARD_ID, 19200);
    if (retVal) {
        commPort = psController->getBoardCommPort(JigaTestInterface::PROG_BOARD_ID);
        testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_SUCCESS_OPEN_SERIAL_PORT);
        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);

        for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + tr(CmdMessageConstants::MSG_SEND_AT_COMMAND);
            addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);

            QString cmd = (progMode == JigaTestInterface::PROG_SERIAL_MODE) ? AtCommandConstants::AT_SM_CMD : AtCommandConstants::AT_PM_CMD;
            psController->serialBoardWrite(JigaTestInterface::PROG_BOARD_ID, cmd, false);

            testMessage = commPort + tr(CmdMessageConstants::MSG_SEPARATOR) + cmd;
            addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);

            QThread::msleep(500);

            recvStr = psController->serialBoardRead(JigaTestInterface::PROG_BOARD_ID);
            testMessage = commPort + ": " + recvStr;
            addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);

            if (recvStr == AtCommandConstants::AT_PROG_SM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " serial!";
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestInterface::PROG_BOARD_ID);
                testMessage = commPort+": "+tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD,JigaTestInterface::PROG_BOARD_ID,testMessage,false);
                return;
            } else if (recvStr == AtCommandConstants::AT_PROG_PM) {
                testMessage = commPort + ": " + tr(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " de programação!";
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, false);
                psController->closeBoardConnection(JigaTestInterface::PROG_BOARD_ID);
                testMessage = commPort+": "+tr(CmdMessageConstants::MSG_SUCCESS_CLOSE_SERIAL_PORT);
                addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD,JigaTestInterface::PROG_BOARD_ID,testMessage,false);
                return;
            }
        }
        psController->closeBoardConnection(JigaTestInterface::PROG_BOARD_ID);
    }
}

int McuBusinessController::uploadFirmware(int programmerId) {
    // Faz o upload do firmware para o MCU.
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
    case JigaTestInterface::USB_PROG_ID:
        optPROG += tr(SystemProperties::MCU_PROG_USB);
        break;
    case JigaTestInterface::SERIAL_PROG_ID:
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

    int retVal = psController->writeFirmware(JigaTestInterface::MCU_FIRMWARE_UPLOAD,JigaTestInterface::MCU1_BOARD_ID,cmdBootUpFuse);
    if (retVal < 0) {
        qDebug() << "retVal =" << retVal;
        return retVal;
    }

    retVal = psController->writeFirmware(JigaTestInterface::MCU_FIRMWARE_UPLOAD,JigaTestInterface::MCU1_BOARD_ID,cmdBootUpHEX);
    if (retVal < 0) {
        qDebug() << "retVal =" << retVal;
        return retVal;
    }

    retVal = psController->writeFirmware(JigaTestInterface::MCU_FIRMWARE_UPLOAD,JigaTestInterface::MCU1_BOARD_ID,cmdAppUpHEX);
    return retVal;
}

bool McuBusinessController::setCanBus1Network() {
    // Configura a rede CAN Bus 1 para o MCU.
    bool retVal = false;
    int resVal;
    QString testMessage;
    int stateMachine;

    // Abre conexão com o programador
    retVal = psController->openBoardConnection(JigaTestInterface::MCU1_BOARD_ID, 19200);
    if (!retVal) {
        return false;
    }

    // Verifica a configuração de rede CAN para ECU3 e ECU4
    resVal = checkCanBus1Network(JigaTestInterface::CAN1_NETWORK_TEST);
    switch (resVal) {
    case EcuBusinessInterface::ERROR_RETRIEVE_REPORT_CODE:
        testMessage = tr(CmdMessageConstants::MSG_ERROR_TO_RUN_TEST) + c1NetworkModel->getBoardDescription(JigaTestInterface::MCU1_BOARD_ID);
        addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID, testMessage, true);
        c1NetworkModel->setTestResult(JigaTestInterface::MCU1_BOARD_ID, JigaTestInterface::CAN1_NETWORK_TEST);
        return false;

    case JigaTestInterface::ECU_CANBUS_1:
        testMessage = tr("ECU3 and ECU4 connected on CANBUS1!");
        addCmdTestMessage(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ALL_BOARDS_ID, testMessage, true);
        return true;

    default:
        stateMachine = McuBusinessInterface::SM_SEL_SL_STATE;
        for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
            // Configurar CAN bus
            switch (stateMachine) {
            case McuBusinessInterface::SM_SEL_SL_STATE:
                sendAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID, AtCommandConstants::AT_SL_CMD);
                retVal = acknowledgeAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID);
                if (retVal) {
                    if (resVal == JigaTestInterface::ECU_CANBUS_2) {
                        stateMachine = McuBusinessInterface::SM_SEL_UD_STATE;
                    } else if (resVal == JigaTestInterface::ECU3_CANBUS1) {
                        stateMachine = McuBusinessInterface::SM_SEL_SU_STATE;
                    } else if (resVal == JigaTestInterface::ECU4_CANBUS1) {
                        stateMachine = McuBusinessInterface::SM_SEL_SD_STATE;
                    }
                }
                break;
            case McuBusinessInterface::SM_SEL_UD_STATE:
                sendAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID, AtCommandConstants::AT_SU_CMD);
                retVal = acknowledgeAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID);
                if (retVal) stateMachine = McuBusinessInterface::SM_SEL_SD_STATE;
                break;
            case McuBusinessInterface::SM_SEL_SU_STATE:
                sendAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID, AtCommandConstants::AT_SU_CMD);
                retVal = acknowledgeAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID);
                if (retVal) stateMachine = McuBusinessInterface::SM_SEL_SV_STATE;
                break;
            case McuBusinessInterface::SM_SEL_SD_STATE:
                sendAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID, AtCommandConstants::AT_SD_CMD);
                retVal = acknowledgeAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID);
                if (retVal) stateMachine = McuBusinessInterface::SM_SEL_SV_STATE;
                break;
            case McuBusinessInterface::SM_SEL_SV_STATE:
                sendAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID, AtCommandConstants::AT_SD_CMD);
                retVal = acknowledgeAtCommand(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::MCU1_BOARD_ID);
                if (retVal) return true;
                break;
            }
        }
        break;
    }

    return false;
}

int McuBusinessController::checkCanBus1Network(int testId) {
    // Verifica a configuração da rede CAN Bus 1.
    QString recvStr = "";
    QString testMessage;
    QString commPort;
    int code = -1;

    commPort = psController->getBoardCommPort(JigaTestInterface::MCU1_BOARD_ID);

    // Envia comando AT para MCU1
    for (int i = 0; i < EcuBusinessInterface::MAX_NUMBER_ATTEMPTS; i++) {
        testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + CmdMessageConstants::MSG_SEND_AT_COMMAND;
        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);

        psController->serialBoardWrite(JigaTestInterface::MCU1_BOARD_ID, AtCommandConstants::AT_SB_CMD, true);

        testMessage = commPort + CmdMessageConstants::MSG_SEPARATOR + AtCommandConstants::AT_SB_CMD;
        addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);

        // Aguardar um momento
        QThread::msleep(500);  // Atraso em milissegundos

        // Obtendo resultado do teste
        recvStr = psController->serialBoardRead(JigaTestInterface::MCU1_BOARD_ID);
        testMessage = commPort + ": " + recvStr;
        addCmdTestMessage(testId, JigaTestInterface::MCU1_BOARD_ID, testMessage, false);

        // Verifica o código retornado
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
