#include "MCUInterfaceTest.h"

// Inicialização do singleton
MCUInterfaceTest* MCUInterfaceTest::instance = nullptr;

MCUInterfaceTest::MCUInterfaceTest() {
    // Criando e configurando o modelo de teste
    TestReportModel* tModel = new TestReportModel(JigaTestInterface::MCU_INTERFACE_TEST, JigaTestInterface::MCU1_BOARD_ID);
    tModel->addIndividualTest(JigaTestInterface::MCU_RST_ACT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_RST_DAC_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_RST_ATT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_IDENT_PORT_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_SEL_CANBUS1_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_SEL_CANBUS2_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_GET_CANBUS_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_TOG_ECU3BUS_ITEST);
    tModel->addIndividualTest(JigaTestInterface::MCU_TOG_ECU4BUS_ITEST);

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
