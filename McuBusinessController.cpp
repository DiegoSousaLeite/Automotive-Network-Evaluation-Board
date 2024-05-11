#include "McuBusinessController.h"
#include <QDebug>

McuBusinessController::McuBusinessController(QObject *parent) :
    QObject(parent),
    psController(PersistenceController::getInstance())
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


