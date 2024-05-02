#include "AnalogOutputTest.h"

// Inicialização do singleton
AnalogOutputTest* AnalogOutputTest::instance = nullptr;

AnalogOutputTest::AnalogOutputTest() {
    // Configurações específicas para cada ECU
    TestReportModel* tModel;

    // Configuração para ECU1
    tModel = new TestReportModel(JigaTestConstants::ANALOG_OUTPUT_TEST, JigaTestConstants::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::AOUT1_LDR_ITEST);
    testReportModel.push_back(tModel);

    // Configuração para ECU2
    tModel = new TestReportModel(JigaTestConstants::ANALOG_OUTPUT_TEST, JigaTestConstants::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::AOUT2_LOOP_ITEST);
    testReportModel.push_back(tModel);

    // Configuração para todos os painéis
    tModel = new TestReportModel(JigaTestConstants::ANALOG_OUTPUT_TEST, JigaTestConstants::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

AnalogOutputTest* AnalogOutputTest::getInstance() {
    if (!instance) {
        instance = new AnalogOutputTest();
    }
    return instance;
}

AnalogOutputTest::~AnalogOutputTest() {
    // Limpeza dos modelos de teste
    for (auto& model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}
