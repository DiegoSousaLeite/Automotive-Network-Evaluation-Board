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

    //Test report for ECU2
    tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST,JigaTestConstants::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::COMM_ECU2_ITEST);
    testReportModel.push_back(tModel);

    //Test report for ECU3
    tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST,JigaTestConstants::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::COMM_ECU3_ITEST);
    testReportModel.push_back(tModel);

    //Test report for ECU4
    tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST,JigaTestConstants::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::COMM_ECU4_ITEST);
    testReportModel.push_back(tModel);

    //Test report for PROG
    tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST,JigaTestConstants::MCU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::COMM_PROG_ITEST);
    tModel->addIndividualTest(JigaTestConstants::COMM_MCU1_ITEST);
    testReportModel.push_back(tModel);

    //Test report for ALL
    tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST,JigaTestConstants::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
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
