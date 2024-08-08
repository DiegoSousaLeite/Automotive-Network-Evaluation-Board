#include "AnalogOutputTest.h"

// Inicialização do singleton
AnalogOutputTest* AnalogOutputTest::instance = nullptr;

AnalogOutputTest::AnalogOutputTest() {
    // Configurações específicas para cada ECU
    TestReportModel* tModel;

    // Configuração para ECU1
    tModel = new TestReportModel(JigaTestInterface::ANALOG_OUTPUT_TEST, JigaTestInterface::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::AOUT1_LDR_ITEST);
    testReportModel.push_back(tModel);

    // Configuração para ECU2
    tModel = new TestReportModel(JigaTestInterface::ANALOG_OUTPUT_TEST, JigaTestInterface::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::AOUT2_LOOP_ITEST);
    testReportModel.push_back(tModel);

    // Configuração para todos os painéis
    tModel = new TestReportModel(JigaTestInterface::ANALOG_OUTPUT_TEST, JigaTestInterface::ALL_BOARDS_ID);
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
