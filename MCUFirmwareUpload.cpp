#include "MCUFirmwareUpload.h"
#include "JigaTestInterface.h"

MCUFirmwareUpload* MCUFirmwareUpload::instance = nullptr;

MCUFirmwareUpload::MCUFirmwareUpload() : GenericTest() {
    // Cria um novo TestReportModel para MCU1
    QSharedPointer<TestReportModel> tModelMCU1(new TestReportModel(JigaTestInterface::MCU_FIRMWARE_UPLOAD, JigaTestInterface::MCU1_BOARD_ID));
    testReportModel.append(tModelMCU1);

    // Cria um novo TestReportModel para todos os painéis
    QSharedPointer<TestReportModel> tModelAll(new TestReportModel(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::ALL_BOARDS_ID));
    testReportModel.append(tModelAll);
}

void MCUFirmwareUpload::addChangeListeners(IFrameListener* frameController) {
    // Adicione o ouvinte ao vetor de ouvintes
    listeners.push_back(frameController);
}

MCUFirmwareUpload* MCUFirmwareUpload::getInstance() {
    if (!instance) {
        instance = new MCUFirmwareUpload();
    }
    return instance;
}
