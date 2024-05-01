#ifndef CAN1NETWORKTEST_H
#define CAN1NETWORKTEST_H

#include "GenericTest.h"
#include "TestReportModel.h"
#include "JigaTestInterface.h"

class CAN1NetworkTest : public GenericTest {
private:
    static CAN1NetworkTest* instance;

    CAN1NetworkTest() {
        TestReportModel* tModel;

        // Test model for ECU1
        tModel = new TestReportModel(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU1_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU2_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU3_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report for ECU2
        tModel = new TestReportModel(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU2_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU1_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU3_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report for ECU3
        tModel = new TestReportModel(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU3_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU1_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU2_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU4_ITEST);
        testReportModel.push_back(tModel);

        // Test report for ECU4
        tModel = new TestReportModel(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ECU4_BOARD_ID);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU1_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU2_ITEST);
        tModel->addIndividualTest(JigaTestConstants::CAN1_ECU3_ITEST);
        testReportModel.push_back(tModel);

        // Test report for ALL
        tModel = new TestReportModel(JigaTestConstants::CAN1_NETWORK_TEST, JigaTestConstants::ALL_BOARDS_ID);
        testReportModel.push_back(tModel);
    }

public:
    static CAN1NetworkTest* getInstance() {
        if (!instance) {
            instance = new CAN1NetworkTest();
        }
        return instance;
    }

    virtual ~CAN1NetworkTest() {}

    CAN1NetworkTest(const CAN1NetworkTest&) = delete;
    CAN1NetworkTest& operator=(const CAN1NetworkTest&) = delete;
};

CAN1NetworkTest* CAN1NetworkTest::instance = nullptr;

#endif // CAN1NETWORKTEST_H
