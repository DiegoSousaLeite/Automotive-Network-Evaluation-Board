#include "LinNetworkTest.h"

// Inicialização do ponteiro estático de instância
LinNetworkTest* LinNetworkTest::instance = nullptr;

LinNetworkTest::LinNetworkTest() {
    // Criando e configurando os modelos de teste para as placas específicas
    TestReportModel* tModel;

    // Modelo de teste para ECU3
    tModel = new TestReportModel(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::LIN1_ECU3_ITEST);
    testReportModel.push_back(tModel);

    // Modelo de teste para ECU4
    tModel = new TestReportModel(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::LIN1_ECU4_ITEST);
    testReportModel.push_back(tModel);

    // Modelo de teste para todos as placas
    tModel = new TestReportModel(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

LinNetworkTest::~LinNetworkTest() {
    for (auto model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}

LinNetworkTest* LinNetworkTest::getInstance() {
    if (!instance) {
        instance = new LinNetworkTest();
    }
    return instance;
}
