#include "MCUInterfaceTest.h"

// Inicialização do singleton
MCUInterfaceTest* MCUInterfaceTest::instance = nullptr;

MCUInterfaceTest::MCUInterfaceTest() {
    // Criando e configurando o modelo de teste
    TestReportModel* tModel = new TestReportModel(JigaTestConstants::MCU_INTERFACE_TEST, JigaTestConstants::MCU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestConstants::MCU_RST_ACT_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_RST_DAC_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_RST_ATT_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_IDENT_PORT_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_SEL_CANBUS1_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_SEL_CANBUS2_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_GET_CANBUS_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_TOG_ECU3BUS_ITEST);
    tModel->addIndividualTest(JigaTestConstants::MCU_TOG_ECU4BUS_ITEST);

    testReportModel.push_back(tModel);
}

MCUInterfaceTest* MCUInterfaceTest::getInstance() {
    if (!instance) {
        instance = new MCUInterfaceTest();
    }
    return instance;
}

MCUInterfaceTest::~MCUInterfaceTest() {
    for (auto model : testReportModel) {
        delete model;
    }
    testReportModel.clear();
}
