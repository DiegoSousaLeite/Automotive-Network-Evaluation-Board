#ifndef ANALOGINPUTTEST_H
#define ANALOGINPUTTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class AnalogInputTest : public GenericTest {
private:
    static AnalogInputTest* instance;

    // Construtor privado
    AnalogInputTest() {
        // Inicializa os modelos de relatório de teste para diferentes ECUs
        TestReportModel* tModel;

        // Configuração para ECU1
        tModel = new TestReportModel(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::AIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);

        // Configuração para ECU2
        tModel = new TestReportModel(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU2_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::AIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);

        // Configuração para ECU3
        tModel = new TestReportModel(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::AIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);

        // Configuração para ECU4
        tModel = new TestReportModel(JigaTestConstants::ANALOG_INPUT_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::AIN1_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN2_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN3_INPUT_ITEST);
        tModel->addIndividualTest(JigaTestConstants::AIN4_INPUT_ITEST);
        testReportModel.push_back(tModel);



        // Test report for ALL BOARDS
        tModel = new TestReportModel(JigaTestInterface::ANALOG_INPUT_TEST, JigaTestInterface::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    // Singleton Access
    static AnalogInputTest* getInstance() {
        if (instance == nullptr) {
            instance = new AnalogInputTest();
        }
        return instance;
    }

    // Destructor
    virtual ~AnalogInputTest() {
        // Limpar todos os modelos criados
        for (auto& model : testReportModel) {
            delete model;
        }
        testReportModel.clear();
    }

    // Evita a cópia e atribuição
    AnalogInputTest(const AnalogInputTest&) = delete;
    AnalogInputTest& operator=(const AnalogInputTest&) = delete;
};

// Inicialização do singleton
AnalogInputTest* AnalogInputTest::instance = nullptr;

#endif // ANALOGINPUTTEST_H
