// CommunicationTest.cpp
#include "CommunicationTest.h"

// Inicializar a instância estática
CommunicationTest* CommunicationTest::instance = nullptr;

CommunicationTest::CommunicationTest() {
    // Implementação do construtor
    TestReportModel* tModel;

    // Test model para ECU1
    tModel = new TestReportModel(JigaTestInterface::COMMUNICATION_TEST, JigaTestInterface::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::COMM_ECU1_ITEST);
    testReportModel.push_back(tModel);

    //Test report for ECU2
    tModel = new TestReportModel(JigaTestInterface::COMMUNICATION_TEST,JigaTestInterface::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::COMM_ECU2_ITEST);
    testReportModel.push_back(tModel);

    //Test report for ECU3
    tModel = new TestReportModel(JigaTestInterface::COMMUNICATION_TEST,JigaTestInterface::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::COMM_ECU3_ITEST);
    testReportModel.push_back(tModel);

    //Test report for ECU4
    tModel = new TestReportModel(JigaTestInterface::COMMUNICATION_TEST,JigaTestInterface::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::COMM_ECU4_ITEST);
    testReportModel.push_back(tModel);

    //Test report for PROG
    tModel = new TestReportModel(JigaTestInterface::COMMUNICATION_TEST,JigaTestInterface::MCU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::COMM_PROG_ITEST);
    tModel->addIndividualTest(JigaTestInterface::COMM_MCU1_ITEST);
    testReportModel.push_back(tModel);

    //Test report for ALL
    tModel = new TestReportModel(JigaTestInterface::COMMUNICATION_TEST,JigaTestInterface::ALL_BOARDS_ID);
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
