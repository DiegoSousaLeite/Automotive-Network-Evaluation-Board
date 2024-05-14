#include "McuFrameController.h"
#include <QDebug>

McuFrameController::McuFrameController(QObject *parent) : FrameController(parent) {

    fwUpdateModel->addChangeListener(this);
}

McuFrameController::~McuFrameController() {
    delete fwUpdateModel;
}

void McuFrameController::setMcuBusinessController(McuBusinessInterface* mcuInterface) {
    bsController = mcuInterface;
}

void McuFrameController::executeFirmwareUpload(int programmer_id) {
    resetTestModel(JigaTestConstants::FIRMWARE_UPLOAD);

    QString testMessage = " iniciado!";
    addHeaderTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage);

    bool retVal = bsController->loadProgrammer(programmer_id);
    if (!retVal) {
        testMessage = CmdMessageConstants::MSG_NOT_FOUND_PROGRAMMER;
        bsController->addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, testMessage, true);
        return;
    }

    if (programmer_id == JigaTestConstants::SERIAL_PROG_ID) {
        int progMode = bsController->getSerialProgrammerMode();
        if (progMode != JigaTestConstants::PROG_PROGRAMMER_MODE) {
            testMessage = QString(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " serial";
            bsController->addCmdTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::PROG_BOARD_ID, testMessage, true);
            bsController->setSerialProgrammerMode(JigaTestConstants::PROG_PROGRAMMER_MODE);
        }
    }

    bsController->uploadFirmware(programmer_id);
    addHeaderTestMessage(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, " finalizado!");
}

void McuFrameController::onPropertyChanged(const QString &property, const QVariant &value) {
    if (property == SystemProperties::TEST_MESSAGE_PROPERTY) {
        qDebug() << ">> " << value.toString();
        emit testMessageChanged(value.toString());
    }
}
