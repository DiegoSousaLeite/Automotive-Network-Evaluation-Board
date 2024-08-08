#include "CANInitTest.h"

// Inicialização do singleton
CANInitTest* CANInitTest::instance = nullptr;

CANInitTest::CANInitTest() {
    TestReportModel* tModel;

    // Test model para ECU1
    tModel = new TestReportModel(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::ICAN1_ECU1_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU2
    tModel = new TestReportModel(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::ICAN1_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestInterface::ICAN2_ECU2_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU3
    tModel = new TestReportModel(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::ICAN1_ECU3_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU4
    tModel = new TestReportModel(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::ICAN1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ALL
    tModel = new TestReportModel(JigaTestInterface::CAN_INIT_TEST, JigaTestInterface::ALL_BOARDS_ID);
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
