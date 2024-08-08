#include "findserialporttest.h"
#include "JigaTestInterface.h"

FindSerialPortTest* FindSerialPortTest::findSerialTestModel = nullptr;

FindSerialPortTest::FindSerialPortTest() : GenericTest() {
    // Cria novos TestReportModel para cada ECU e MCU com testes individuais
    QSharedPointer<TestReportModel> tModelECU1(new TestReportModel(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::ECU1_BOARD_ID));
    tModelECU1->addIndividualTest(JigaTestInterface::FIND_ECU1_ITEST);
    testReportModel.append(tModelECU1);

    QSharedPointer<TestReportModel> tModelECU2(new TestReportModel(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::ECU2_BOARD_ID));
    tModelECU2->addIndividualTest(JigaTestInterface::FIND_ECU2_ITEST);
    testReportModel.append(tModelECU2);

    QSharedPointer<TestReportModel> tModelECU3(new TestReportModel(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::ECU3_BOARD_ID));
    tModelECU3->addIndividualTest(JigaTestInterface::FIND_ECU3_ITEST);
    testReportModel.append(tModelECU3);

    QSharedPointer<TestReportModel> tModelECU4(new TestReportModel(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::ECU4_BOARD_ID));
    tModelECU4->addIndividualTest(JigaTestInterface::FIND_ECU4_ITEST);
    testReportModel.append(tModelECU4);

    QSharedPointer<TestReportModel> tModelMCU(new TestReportModel(JigaTestInterface::FIND_SERIAL_PORT_TEST, JigaTestInterface::MCU1_BOARD_ID));
    tModelMCU->addIndividualTest(JigaTestInterface::FIND_MCU1_ITEST);
    testReportModel.append(tModelMCU);
}

FindSerialPortTest* FindSerialPortTest::getInstance() {
    if (!findSerialTestModel) {
        findSerialTestModel = new FindSerialPortTest();
    }
    return findSerialTestModel;
}
