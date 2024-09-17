#include "McuFrameController.h"
#include <QDebug>

// Construtor da classe McuFrameController
McuFrameController::McuFrameController(QObject *parent) : FrameController(parent) {
    // Adiciona o próprio controlador como listener de mudanças ao modelo de firmware MCU
    mcuFwUpModel->addChangeListeners(this);
}

McuFrameController::~McuFrameController() {
    // Libera a memória alocada para o modelo de firmware MCU
    delete mcuFwUpModel;
}

// Define o controlador de negócios da MCU
void McuFrameController::setMcuBusinessController(McuBusinessController* mcuInterface) {
    bsController = mcuInterface;
}

// Executa o upload do firmware para o MCU usando um programador específico
void McuFrameController::executeFirmwareUpload(int programmer_id) {
    // Reseta o modelo de teste para o upload de firmware do MCU
    resetTestModel(JigaTestInterface::MCU_FIRMWARE_UPLOAD);

    // Adiciona uma mensagem de início ao teste
    QString testMessage = " iniciado!";
    addHeaderTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage);

    // Tenta carregar o programador especificado pelo ID
    bool retVal = bsController->loadProgrammer(programmer_id);
    if (!retVal) {
        // Se o programador não foi encontrado, adiciona uma mensagem de erro e retorna
        testMessage = CmdMessageConstants::MSG_NOT_FOUND_PROGRAMMER;
        bsController->addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, testMessage, true);
        return;
    }

    // Se o programador é do tipo serial, verifica o modo do programador
    if (programmer_id == JigaTestInterface::SERIAL_PROG_ID) {
        int progMode = bsController->getSerialProgrammerMode();
        if (progMode != JigaTestInterface::PROG_PROGRAMMER_MODE) {
            // Se o modo não está configurado para programador, adiciona uma mensagem e ajusta o modo
            testMessage = QString(CmdMessageConstants::MSG_PROGRAMMER_MODE) + " serial";
            bsController->addCmdTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::PROG_BOARD_ID, testMessage, true);
            bsController->setSerialProgrammerMode(JigaTestInterface::PROG_PROGRAMMER_MODE);
        }
    }

    // Inicia o upload do firmware
    bsController->uploadFirmware(programmer_id);

    // Adiciona uma mensagem indicando o fim do upload de firmware
    addHeaderTestMessage(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID, " finalizado!");
}

// Slot chamado quando uma propriedade é alterada
void McuFrameController::onPropertyChanged(const QString &property, const QVariant &value) {
    // Verifica se a propriedade alterada é a de mensagem de teste
    if (property == SystemProperties::TEST_MESSAGE_PROPERTY) {
        qDebug() << ">> " << value.toString();
        emit testMessageChanged(value.toString()); // Emite o sinal de mudança de mensagem de teste
    }
}
