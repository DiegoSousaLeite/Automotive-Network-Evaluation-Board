#ifndef CANINITTEST_H
#define CANINITTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CANInitTest : public GenericTest {
private:
    static CANInitTest* instance;

    // Construtor privado
    CANInitTest() {
        TestReportModel* tModel;

        // Test model para ECU1
        tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU1_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU2
        tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU2_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU2_ITEST);
        tModel->addIndividualTest(JigaTestConstants::ICAN2_ECU2_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU3
        tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU3_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU4
        tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::ICAN1_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ALL
        tModel = new TestReportModel(JigaTestConstants::CAN_INIT_TEST, JigaTestConstants::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    static CANInitTest* getInstance() {
        if (!instance) {
            instance = new CANInitTest();
        }
        return instance;
    }

    virtual ~CANInitTest() {
        // Liberar os TestReportModels
        for (auto& model : testReportModel) {
            delete model;
        }
    }

    CANInitTest(const CANInitTest&) = delete;
    CANInitTest& operator=(const CANInitTest&) = delete;
};

// Inicialização da instância estática
CANInitTest* CANInitTest::instance = nullptr;

#endif // CANINITTEST_H
