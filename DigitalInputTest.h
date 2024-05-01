#ifndef DIGITALINPUTTEST_H
#define DIGITALINPUTTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class DigitalInputTest : public GenericTest {
private:
    static DigitalInputTest* instance;

    DigitalInputTest() {
        TestReportModel* tModel;

        // Test model for ECU1
        tModel = new TestReportModel(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::DIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);

        // Test model for ECU2
        tModel = new TestReportModel(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU2_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::DIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);

        // Test model for ECU3
        tModel = new TestReportModel(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::DIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);

        // Test model for ECU4
        tModel = new TestReportModel(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::DIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::DIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);

        // Test model for MCU1
        tModel = new TestReportModel(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::MCU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::MSE1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::MSE2_INPUT_ITEST);
        testReportModel.push_back(tModel);


        // Test report for ALL
        tModel = new TestReportModel(JigaTestConstants::DIGITAL_INPUT_TEST, JigaTestConstants::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    static DigitalInputTest* getInstance() {
        if (!instance) {
            instance = new DigitalInputTest();
        }
        return instance;
    }

    virtual ~DigitalInputTest() {
        for (auto& model : testReportModel) {
            delete model;
        }
    }

    DigitalInputTest(const DigitalInputTest&) = delete;
    DigitalInputTest& operator=(const DigitalInputTest&) = delete;
};

// Inicialização da instância estática
DigitalInputTest* DigitalInputTest::instance = nullptr;

#endif // DIGITALINPUTTEST_H
