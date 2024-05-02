#include "CANInitTest.h"

// Inicialização do singleton
CANInitTest* CANInitTest::instance = nullptr;

CANInitTest::CANInitTest() {
    TestReportModel* tModel;

    // Test model para ECU1
    tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU1_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU2
    tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestConstants::ICAN2_ECU2_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU3
    tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU3_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU4
    tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ALL
    tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

CANInitTest* CANInitTest::getInstance() {
    if (!instance) {
        instance = new CANInitTest();
    }
    return instance;
}

CANInitTest::~CANInitTest() {
    for (auto& model : testReportModel) {
        delete model;
    }
}
