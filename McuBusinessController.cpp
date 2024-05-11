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



