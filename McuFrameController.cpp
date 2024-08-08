#include "McuFrameController.h"
#include <QDebug>

McuFrameController::McuFrameController(QObject *parent) : FrameController(parent) {

    mcuFwUpModel->addChangeListeners(this);
}

McuFrameController::~McuFrameController() {
    delete mcuFwUpModel;
}

void McuFrameController::setMcuBusinessController(McuBusinessController* mcuInterface) {
    bsController = mcuInterface;
}

void McuFrameController::executeFirmwareUpload(int programmer_id) {
    resetTestModel(JigaTestInterface::MCU_FIRMWARE_UPLOAD);

    QString testMessage = " iniciado!";
    addHeaderTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage);

    bool retVal = bsController->loadProgrammer(programmer_id);
    if (!retVal) {
        testMessage = CmdMessageConstants::MSG_NOT_FOUND_PROGRAMMER;
        bsController->addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, true);
        return;
    }

    if (programmer_id == JigaTestInterface::SERIAL_PROG_ID) {
        int progMode = bsController->getSerialProgrammerMode();
        if (progMode != JigaTestInterface::PROG_PROGRAMMER_MODE) {
            testMessage = QString(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " serial";
            bsController->addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, true);
            bsController->setSerialProgrammerMode(JigaTestInterface::PROG_PROGRAMMER_MODE);
        }
    }

    bsController->uploadFirmware(programmer_id);
    addHeaderTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, " finalizado!");
}

void McuFrameController::onPropertyChanged(const QString &property, const QVariant &value) {
    if (property == SystemProperties::TEST_MESSAGE_PROPERTY) {
        qDebug() << ">> " << value.toString();
        emit testMessageChanged(value.toString());
    }
}
