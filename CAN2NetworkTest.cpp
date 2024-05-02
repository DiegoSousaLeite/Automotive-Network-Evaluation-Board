#include "CAN2NetworkTest.h"

// Inicialização do singleton
CAN2NetworkTest* CAN2NetworkTest::instance = nullptr;

CAN2NetworkTest::CAN2NetworkTest() {
    // Configurações específicas para cada ECU
    TestReportModel* tModel;


    // Test report para ECU2
    tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::CAN2_ECU3_ITEST);
    tModel->addIndividualTest(JigaTestConstants::CAN2_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU3
    tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::CAN2_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestConstants::CAN2_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ECU4
    tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::CAN2_ECU2_ITEST);
    tModel->addIndividualTest(JigaTestConstants::CAN2_ECU3_ITEST);
    testReportModel.push_back(tModel);

    // Test report para ALL
    tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

CAN2NetworkTest* CAN2NetworkTest::getInstance() {
    if (!instance) {
        instance = new CAN2NetworkTest();
    }
    return instance;
}

CAN2NetworkTest::~CAN2NetworkTest() {
    // Limpeza dos modelos de teste
    for (auto& model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}
