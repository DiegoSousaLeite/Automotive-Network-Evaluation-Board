#ifndef ANALOGOUTPUTTEST_H
#define ANALOGOUTPUTTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class AnalogOutputTest : public GenericTest {
private:
    static AnalogOutputTest* instance;

    // Construtor privado
    AnalogOutputTest() {
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

public:
    // Singleton Access
    static AnalogOutputTest* getInstance() {
        if (!instance) {
            instance = new AnalogOutputTest();
        }
        return instance;
    }

    // Destructor
    virtual ~AnalogOutputTest() {
        // Limpar todos os modelos criados
        for (auto& model : testReportModel) {
            delete model;
        }
        testReportModel.clear();
    }

    // Impedir cópia e atribuição
    AnalogOutputTest(const AnalogOutputTest&) = delete;
    AnalogOutputTest& operator=(const AnalogOutputTest&) = delete;
};

// Inicialização do singleton
AnalogOutputTest* AnalogOutputTest::instance = nullptr;

#endif // ANALOGOUTPUTTEST_H
