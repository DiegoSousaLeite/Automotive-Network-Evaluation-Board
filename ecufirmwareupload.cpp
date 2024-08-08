#include "ecufirmwareupload.h"
#include "JigaTestInterface.h"

ECUFirmwareUpload* ECUFirmwareUpload::ecuFwUploadTestModel = nullptr;

ECUFirmwareUpload::ECUFirmwareUpload() : GenericTest() {
    // Cria novos TestReportModel para cada ECU
    QSharedPointer<TestReportModel> tModelECU1(new TestReportModel(JigaTestInterface::ECU_FIRMWARE_UPLOAD, JigaTestInterface::ECU1_BOARD_ID));
    testReportModel.append(tModelECU1);

    QSharedPointer<TestReportModel> tModelECU2(new TestReportModel(JigaTestInterface::ECU_FIRMWARE_UPLOAD, JigaTestInterface::ECU2_BOARD_ID));
    testReportModel.append(tModelECU2);

    QSharedPointer<TestReportModel> tModelECU3(new TestReportModel(JigaTestInterface::ECU_FIRMWARE_UPLOAD, JigaTestInterface::ECU3_BOARD_ID));
    testReportModel.append(tModelECU3);

    QSharedPointer<TestReportModel> tModelECU4(new TestReportModel(JigaTestInterface::ECU_FIRMWARE_UPLOAD, JigaTestInterface::ECU4_BOARD_ID));
    testReportModel.append(tModelECU4);

    // Cria um novo TestReportModel para todos os painéis
    QSharedPointer<TestReportModel> tModelAll(new TestReportModel(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::ALL_BOARDS_ID));
    testReportModel.append(tModelAll);
}

ECUFirmwareUpload* ECUFirmwareUpload::getInstance() {
    if (!ecuFwUploadTestModel) {
        ecuFwUploadTestModel = new ECUFirmwareUpload();
    }
    return ecuFwUploadTestModel;
}
