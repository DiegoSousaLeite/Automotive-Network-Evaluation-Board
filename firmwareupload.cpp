#include "firmwareupload.h"
#include "testreportmodel.h"
#include "JigaTestInterface.h"

FirmwareUpload* FirmwareUpload::instance = nullptr;

FirmwareUpload::FirmwareUpload() : GenericTest() {
    // Cria um novo TestReportModel para MCU1
    TestReportModel* tModelMCU1 = new TestReportModel(JigaTestConstants::FIRMWARE_UPLOAD, JigaTestConstants::MCU1_BOARD_ID, this);
    testReportModels.append(tModelMCU1);

    // Cria um novo TestReportModel para todos os painéis
    TestReportModel* tModelAll = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ALL_BOARDS_ID, this);
    testReportModels.append(tModelAll);
}

FirmwareUpload* FirmwareUpload::getInstance() {
    if (!instance) {
        instance = new FirmwareUpload();
    }
    return instance;
}
