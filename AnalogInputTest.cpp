#include "AnalogInputTest.h"

// Inicialização do singleton
AnalogInputTest* AnalogInputTest::instance = nullptr;

AnalogInputTest::AnalogInputTest() {
    // Inicializa os modelos de relatório de teste para diferentes ECUs
    TestReportModel* tModel;

    // Configuração para ECU1
    tModel = new TestReportModel(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::AIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);

    // Configuração para ECU2
    tModel = new TestReportModel(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::AIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);

    // Configuração para ECU3
    tModel = new TestReportModel(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::AIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);

    // Configuração para ECU4
    tModel = new TestReportModel(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::AIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::AIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);



    // Test report for ALL BOARDS
    tModel = new TestReportModel(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}


AnalogInputTest* AnalogInputTest::getInstance() {
    if (instance == nullptr) {
        instance = new AnalogInputTest();
    }
    return instance;
}

AnalogInputTest::~AnalogInputTest() {
    // Limpar todos os modelos criados
    for (auto& model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}
