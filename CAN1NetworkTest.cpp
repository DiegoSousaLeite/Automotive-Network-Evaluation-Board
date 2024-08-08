#include "CAN1NetworkTest.h"

// Inicialização do singleton
CAN1NetworkTest* CAN1NetworkTest::instance = nullptr;

CAN1NetworkTest::CAN1NetworkTest() {
    // Configurações específicas para cada ECU
    TestReportModel* tModel;

    // Test model for ECU1
    tModel = new TestReportModel(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU3_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report for ECU2
    tModel = new TestReportModel(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU1_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU3_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report for ECU3
    tModel = new TestReportModel(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU1_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report for ECU4
    tModel = new TestReportModel(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU1_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestInterface::CAN1_ECU3_ITEST);
    testReportModel.push_back(tModel);

    // Test report for ALL
    tModel = new TestReportModel(JigaTestInterface::CAN1_NETWORK_TEST, JigaTestInterface::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

CAN1NetworkTest* CAN1NetworkTest::getInstance() {
    if (!instance) {
        instance = new CAN1NetworkTest();
    }
    return instance;
}

CAN1NetworkTest::~CAN1NetworkTest() {
    // Limpeza dos modelos de teste
    for (auto& model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}
