#ifndef COMMUNICATIONTEST_H
#define COMMUNICATIONTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CommunicationTest : public GenericTest {
private:
    static CommunicationTest* instance;

    // Construtor privado
    CommunicationTest() {
        TestReportModel* tModel;

        // Test model para ECU1
        tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::COMM_ECU1_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU2
        tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU2_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::COMM_ECU2_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU3
        tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::COMM_ECU3_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU4
        tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::COMM_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report para MCU1 e Programmer
        tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::MCU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::COMM_PROG_ITEST);
        tModel->addIndividualTest(JigaTestConstants::COMM_MCU1_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ALL
        tModel = new TestReportModel(JigaTestConstants::COMMUNICATION_TEST, JigaTestConstants::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    static CommunicationTest* getInstance() {
        if (!instance) {
            instance = new CommunicationTest();
        }
        return instance;
    }

    virtual ~CommunicationTest() {
        // Limpar os TestReportModels
        for (auto& model : testReportModel) {
            delete model;
        }
    }

    CommunicationTest(const CommunicationTest&) = delete;
    CommunicationTest& operator=(const CommunicationTest&) = delete;
};

// Inicialização da instância estática
CommunicationTest* CommunicationTest::instance = nullptr;

#endif // COMMUNICATIONTEST_H
