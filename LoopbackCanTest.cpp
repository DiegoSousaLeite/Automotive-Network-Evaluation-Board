#include "LoopbackCanTest.h"

// Inicialização do singleton
LoopbackCanTest* LoopbackCanTest::instance = nullptr;

LoopbackCanTest::LoopbackCanTest() {
    TestReportModel* tModel;

    // Test model para ECU1
    tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::LBC1_ECU1_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU2
    tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::LBC1_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestConstants::LBC2_ECU2_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU3
    tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::LBC1_ECU3_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU4
    tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::LBC1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ALL
    tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

LoopbackCanTest* LoopbackCanTest::getInstance() {
    if (!instance) {
        instance = new LoopbackCanTest();
    }
    return instance;
}

LoopbackCanTest::~LoopbackCanTest() {
    for (auto model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}
