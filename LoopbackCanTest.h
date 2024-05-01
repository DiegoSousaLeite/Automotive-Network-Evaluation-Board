#ifndef LOOPBACKCANTEST_H
#define LOOPBACKCANTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class LoopbackCanTest : public GenericTest {
private:
    static LoopbackCanTest* instance;

    // Constructor privado
    LoopbackCanTest() {
        TestReportModel* tModel;

        // Test model para ECU1
        tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::LBC1_ECU1_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU2
        tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU2_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::LBC1_ECU2_ITEST);
        tModel->addIndividualTest(JigaTestConstants::LBC2_ECU2_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU3
        tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::LBC1_ECU3_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU4
        tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::LBC1_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ALL
        tModel = new TestReportModel(JigaTestConstants::LOOPBACK_CAN_TEST, JigaTestConstants::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    // Destructor
    virtual ~LoopbackCanTest() {
        for (auto model : testReportModel) {
            delete model;
        }
    }

    // Método para obter a instância singleton
    static LoopbackCanTest* getInstance() {
        if (instance == nullptr) {
            instance = new LoopbackCanTest();
        }
        return instance;
    }

    // Impedir cópia e atribuição
    LoopbackCanTest(const LoopbackCanTest&) = delete;
    LoopbackCanTest& operator=(const LoopbackCanTest&) = delete;
};

// Inicialização da instância estática
LoopbackCanTest* LoopbackCanTest::instance = nullptr;

#endif // LOOPBACKCANTEST_H
