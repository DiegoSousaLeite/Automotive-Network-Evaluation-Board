#ifndef CAN2NETWORKTEST_H
#define CAN2NETWORKTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CAN2NetworkTest : public GenericTest {
private:
    static CAN2NetworkTest* instance;

    // Construtor privado
    CAN2NetworkTest() {
        TestReportModel* tModel;

        // Test report para ECU2
        tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU2_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::CAN2_ECU3_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN2_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU3
        tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::CAN2_ECU2_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN2_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ECU4
        tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::CAN2_ECU2_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN2_ECU3_ITEST);
        testReportModel.push_back(tModel);

        // Test report para ALL
        tModel = new TestReportModel(JigaTestConstants::CAN2_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    static CAN2NetworkTest* getInstance() {
        if (instance == nullptr) {
            instance = new CAN2NetworkTest();
        }
        return instance;
    }

    virtual ~CAN2NetworkTest() {}

    CAN2NetworkTest(const CAN2NetworkTest&) = delete;
    CAN2NetworkTest& operator=(const CAN2NetworkTest&) = delete;
};

// Inicialização da instância estática
CAN2NetworkTest* CAN2NetworkTest::instance = nullptr;

#endif // CAN2NETWORKTEST_H
