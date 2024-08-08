#include <gtest/gtest.h>
#include <QDebug>
#include <QCoreApplication>
#include "PersistenceController.h"
#include "EcuBusinessController.h"
#include "FrameController.h"
#include "EcuFrameController.h"


TEST(PersistenceControllerTest, LoadSerialCommPorts) {
    PersistenceController* controller = PersistenceController::getInstance();
    int result = controller->loadSerialCommPorts();
    ASSERT_GT(result, 0);  // Verifica se o resultado é maior que 0
}

TEST(PersistenceControllerTest,GetCommPortFound){
    PersistenceController* controller = PersistenceController::getInstance();
    int result = controller->getCommPortFound(-1);
    ASSERT_EQ(result,-1);
}

TEST(PersistenceControllerTest,OpenConnection){
    PersistenceController* controller = PersistenceController::getInstance();
    int result = controller->openConnection(2,115200);
    ASSERT_EQ(result,true);
}

TEST(EcuBusinessControllerTest, LoadBoard) {
    EcuBusinessController businessController;

    int result = businessController.loadBoard(JigaTestInterface::MCU_RST_ATT_TEST, JigaTestInterface::ECU4_BOARD_ID );
    ASSERT_EQ(result, ErrorCodeInterface::SUCCESS);  // Verifique se o resultado é igual a SUCCESS
}

//TEST(EcuFrameControllerTest, ExecuteTest){
//    EcuFrameController frameController;

//    frameController.executeTest(JigaTestInterface::MCU_RST_ATT_TEST, JigaTestInterface::MCU1_BOARD_ID);
//}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    QCoreApplication app(argc, argv);  // Inicializa o QCoreApplication

    int result = RUN_ALL_TESTS();

    return result;
}
