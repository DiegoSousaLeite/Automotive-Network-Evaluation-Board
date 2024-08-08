#include "DigitalInputTest.h"

// Inicialização do singleton
DigitalInputTest* DigitalInputTest::instance = nullptr;

DigitalInputTest::DigitalInputTest() {
    TestReportModel* tModel;

    // Test model for ECU1
    tModel = new TestReportModel(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::ECU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::DIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);

    // Test model for ECU2
    tModel = new TestReportModel(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::ECU2_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::DIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);

    // Test model for ECU3
    tModel = new TestReportModel(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::ECU3_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::DIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);

    // Test model for ECU4
    tModel = new TestReportModel(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::ECU4_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::DIN1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN2_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN3_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::DIN4_INPUT_ITEST);
    testReportModel.push_back(tModel);

    // Test model for MCU1
    tModel = new TestReportModel(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::MCU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::MSE1_INPUT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MSE2_INPUT_ITEST);
    testReportModel.push_back(tModel);


    // Test report for ALL
    tModel = new TestReportModel(JigaTestInterface::DIGITAL_INPUT_TEST, JigaTestInterface::ALL_BOARDS_ID);
    testReportModel.push_back(tModel);
}

DigitalInputTest* DigitalInputTest::getInstance() {
    if (!instance) {
        instance = new DigitalInputTest();
    }
    return instance;
}

DigitalInputTest::~DigitalInputTest() {
    // Limpeza dos modelos de teste
    for (auto& model : testReportModel) {
        delete model;
    }
}
