#include "CANLoopbackTest.h"

// Inicialização do singleton
CANLoopbackTest* CANLoopbackTest::instance = nullptr;

CANLoopbackTest::CANLoopbackTest() {
    TestReportModel* tModel;

    // Test model para ECU1
    tModel = new TestReportModel(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::LBC1_ECU1_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU2
    tModel = new TestReportModel(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::LBC1_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestInterface::LBC2_ECU2_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU3
    tModel = new TestReportModel(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::LBC1_ECU3_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU4
    tModel = new TestReportModel(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::LBC1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ALL
    tModel = new TestReportModel(JigaTestInterface::CAN_LOOPBACK_TEST, JigaTestInterface::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

CANLoopbackTest* CANLoopbackTest::getInstance() {
    if (!instance) {
        instance = new CANLoopbackTest();
    }
    return instance;
}

CANLoopbackTest::~CANLoopbackTest() {
    for (auto model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}
