#ifndef LINNETWORKTEST_H
#define LINNETWORKTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class LinNetworkTest : public GenericTest {
private:
    static LinNetworkTest* instance;

    LinNetworkTest() {
        // Criando e configurando os modelos de teste para as placas específicas
        TestReportModel* tModel;

        // Modelo de teste para ECU3
        tModel = new TestReportModel(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::LIN1_ECU3_ITEST);
        testReportModel.push_back(tModel);

        // Modelo de teste para ECU4
        tModel = new TestReportModel(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::LIN1_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Modelo de teste para todos as placas
        tModel = new TestReportModel(JigaTestConstants::LIN_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    ~LinNetworkTest() {
        for (auto model : testReportModel) {
            delete model;
        }
    }

    static LinNetworkTest* getInstance() {
        if (!instance) {
            instance = new LinNetworkTest();
        }
        return instance;
    }

    LinNetworkTest(const LinNetworkTest&) = delete;
    LinNetworkTest& operator=(const LinNetworkTest&) = delete;
};

// Inicialização do ponteiro estático de instância
LinNetworkTest* LinNetworkTest::instance = nullptr;

#endif // LINNETWORKTEST_H
