// CommunicationTest.cpp
#include "CommunicationTest.h"

// Inicializar a instância estática
CommunicationTest* CommunicationTest::instance = nullptr;

CommunicationTest::CommunicationTest() {
    // Implementação do construtor
    TestReportModel* tModel;

    // Test model para ECU1
    tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::COMM_ECU1_ITEST);
    testReportModel.push_back(tModel);

    // Repita para outros casos...
}

CommunicationTest* CommunicationTest::getInstance() {
    if (!instance) {
        instance = new CommunicationTest();
    }
    return instance;
}

CommunicationTest::~CommunicationTest() {
    // Limpar os TestReportModels
    for (auto& model : testReportModel) {
        delete model;
    }
}
