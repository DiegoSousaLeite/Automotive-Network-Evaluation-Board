#ifndef MCUINTERFACETEST_H
#define MCUINTERFACETEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class MCUInterfaceTest : public GenericTest {
private:
    static MCUInterfaceTest* instance;

    // Constructor privado
    MCUInterfaceTest() {
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

public:
    // Destructor
    virtual ~MCUInterfaceTest() {
        for (auto model : testReportModel) {
            delete model;
        }
    }

    // Método para obter a instância singleton
    static MCUInterfaceTest* getInstance() {
        if (instance == nullptr) {
            instance = new MCUInterfaceTest();
        }
        return instance;
    }

    // Impedir cópia e atribuição
    MCUInterfaceTest(const MCUInterfaceTest&) = delete;
    MCUInterfaceTest& operator=(const MCUInterfaceTest&) = delete;
};

// Inicialização da instância estática
MCUInterfaceTest* MCUInterfaceTest::instance = nullptr;

#endif // MCUINTERFACETEST_H
