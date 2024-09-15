#include "JigaView.h"
#include "EcuFrameController.h"
#include "McuFrameController.h"
#include "JigaTestInterface.h"
#include "MenuOptionsInterface.h"


JigaView::JigaView(QObject *parent) : QObject(parent),
    ecuFmController(nullptr),
    mcuFmController(nullptr)
{

    mainMenu = MainMenu::getInstance();
    anOutputMenu= AnalogOutputMenu::getInstance();
    c1NetworkMenu = CAN1NetworkMenu::getInstance();
    c2NetworkMenu = CAN2NetworkMenu::getInstance();
    cInitMenu = CANInitMenu::getInstance();
    cLoopbackMenu = CANLoopbackMenu::getInstance();
    commMenu = CommunicationMenu::getInstance();
    diInputMenu = DigitalInputMenu::getInstance();
    ecuUploadMenu = EcuUploadMenu::getInstance();
    lnNetworkMenu = LINNetworkMenu::getInstance();
    loadSerialPortMenu = LoadSerialPortsMenu::getInstance();
    repTestMenu = ReportTestMenus::getInstance();
}

void JigaView::setEcuFrameController(EcuFrameController *controller)
{
    ecuFmController = controller;
}

void JigaView::setMcuFrameController(McuFrameController *controller)
{
    mcuFmController = controller;
}

void JigaView::start()
{
    QTextStream input(stdin);
    QString line;
    bool keepRunning = true;

    while (keepRunning) {
        // Exibir o menu de opções
        mainMenu->printMainMenu();

        line = input.readLine();
        if (line.isEmpty()) {
            continue;  // Continuar se a entrada estiver vazia
        }

        char opt = line[0].toLatin1();
        switch (opt) {
        case MenuOptionsInterface::OPT_COMMUNICATION_TEST:
            qDebug() << "Communication Test selected!";
            selectCommunicationTest();
            break;
        case MenuOptionsInterface::OPT_FIRMWARE_UPLOAD:
            qDebug() << "Gravação de firmware selecionada!";
            selectFirmwareUpload();
            break;
        case MenuOptionsInterface::OPT_DIGITAL_INPUT_TEST:
            qDebug() << "Teste das entradas digitais selecionado!";
            selectDigitalInputTest();
            break;
        case MenuOptionsInterface::OPT_MCU_INTERFACE_TEST:
            qDebug() << "Teste da MCU1 selecionado!";
            selectMcuInterfaceTest();
            break;
        case MenuOptionsInterface::OPT_ANALOG_INPUT_TEST:
            qDebug() << "Teste das entradas analógicas selecionado!";
                selectAnalogInputTest();
            break;
        case MenuOptionsInterface::OPT_ANALOG_OUTPUT_TEST:
            qDebug() << "Teste das saídas analógicas selecionado!";
            selectAnalogOutputTest();
            break;
        case MenuOptionsInterface::OPT_CAN_INIT_TEST:
            qDebug() << "Teste de inicializaçao do controlador CAN selecionado!";
                selectCanInitTest();
            break;
        case MenuOptionsInterface::OPT_LOOPBACK_CAN_TEST:
            qDebug() << "este de loopback CAN selecionado!";
            selectLoopbackCanTest();
            break;
        case MenuOptionsInterface::OPT_CAN1_NETWORK_TEST:
            qDebug() << "Teste da rede CAN BUS1 selecionado!";
            selectCan1NetworkTest();
            break;
        case MenuOptionsInterface::OPT_CAN2_NETWORK_TEST:
            qDebug() << "Teste da rede CAN BUS2 selecionado!";
            selectCan2NetworkTest();
            break;
        case MenuOptionsInterface::OPT_LIN_NETWORK_TEST:
            qDebug() << "Teste da rede LIN selecionado!";
            selectLinNetworkTest();
            break;
        case MenuOptionsInterface::OPT_EXECUTE_ALL_TEST:
            qDebug() << "Execução automática dos testes!";
            selectExecuteAllTests();
            break;
        case MenuOptionsInterface::OPT_REPORT_ALL_TEST:
            qDebug() << "Emissão de relatório dos testes!";
            selectReportTest();
            break;
        case MenuOptionsInterface::OPT_LOAD_SERIAL_PORT_TEST:
            qDebug() << "Teste de carregamento das portas seriais!";
            selectLoadSerialPortTest();
            break;
        case 'x':
            qDebug() << "Exiting...";
            keepRunning = false;  // Sair do loop
            break;
        default:
            qDebug() << "Invalid option!";
            break;
        }
    }
}


void JigaView::selectCommunicationTest()
{
    char opt;
    while (true) {
        commMenu->printOptionMenu();
        opt = getchar();
        switch (opt) {
        case MenuOptionsInterface::OPT_ECU1_SEL:
            qDebug() << "Communication with ECU1 selected!";
            startCommunicationTest(JigaTestInterface::ECU1_BOARD_ID);
            break;
        case MenuOptionsInterface::OPT_ECU2_SEL:
            qDebug() << "Communication with ECU2 selected!";
            startCommunicationTest(JigaTestInterface::ECU2_BOARD_ID);
            break;
        case MenuOptionsInterface::OPT_ECU3_SEL:
            qDebug() << "Communication with ECU3 selected!";
            startCommunicationTest(JigaTestInterface::ECU3_BOARD_ID);
            break;
        case MenuOptionsInterface::OPT_ECU4_SEL:
            qDebug() << "Communication with ECU4 selected!";
            startCommunicationTest(JigaTestInterface::ECU4_BOARD_ID);
            break;
        case MenuOptionsInterface::OPT_MCU1_SEL:
            qDebug() << "Communication with MCU1 selected!";
            startCommunicationTest(JigaTestInterface::MCU1_BOARD_ID);
            break;
        case MenuOptionsInterface::OPT_ALL_SEL:
            qDebug() << "Communication with All Boards selected!";
            startCommunicationTest(JigaTestInterface::ALL_BOARDS_ID);
            break;            
        case 'r':
            return;
        default:
            qDebug() << "Invalid option!";
            break;
        }
    }
}

void JigaView::selectMcuInterfaceTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        mcuInterfaceMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_IDENTIFY_COMM_PORT:
            qDebug() << "Identificar porta!";
            startMCUInterfaceTest(JigaTestInterface::MCU_IDENT_PORT_TEST);
            break;

        case MenuOptionsInterface::OPT_SELECT_CANBUS1:
            qDebug() << "Seleciona CANBUS1!";
            startMCUInterfaceTest(JigaTestInterface::MCU_SEL_CANBUS1_TEST);
            break;

        case MenuOptionsInterface::OPT_SELECT_CANBUS2:
            qDebug() << "Seleciona CANBUS2!";
            startMCUInterfaceTest(JigaTestInterface::MCU_SEL_CANBUS2_TEST);
            break;

        case MenuOptionsInterface::OPT_SET_EXT_RST:
            qDebug() << "Seleciona ativa reset externo!";
            startMCUInterfaceTest(JigaTestInterface::MCU_RST_ACT_TEST);
            break;

        case MenuOptionsInterface::OPT_RESET_EXT_RST:
            qDebug() << "Seleciona desativa reset externo!";
            startMCUInterfaceTest(JigaTestInterface::MCU_RST_DAC_TEST);
            break;

        case MenuOptionsInterface::OPT_RESET_EXT_RTT:
            qDebug() << "Seleciona reset externo (timeout)!";
            startMCUInterfaceTest(JigaTestInterface::MCU_RST_ATT_TEST);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectDigitalInputTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        diInputMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_ECU1_SEL:
            qDebug() << "Teste das entradas digitais com a ECU1!";
            startDigitalInputTest(JigaTestInterface::ECU1_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU2_SEL:
            qDebug() << "Teste das entradas digitais com a ECU2!";
            startDigitalInputTest(JigaTestInterface::ECU2_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU3_SEL:
            qDebug() << "Teste das entradas digitais com a ECU3!";
            startDigitalInputTest(JigaTestInterface::ECU3_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU4_SEL:
            qDebug() << "Teste das entradas digitais com a ECU4!";
            startDigitalInputTest(JigaTestInterface::ECU4_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_MCU1_SEL:
            qDebug() << "Teste das entradas digitais com a MCU1!";
            startDigitalInputTest(JigaTestInterface::MCU1_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ALL_SEL:
            qDebug() << "Teste das entradas digitais com todos!";
            startDigitalInputTest(JigaTestInterface::ALL_BOARDS_ID);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectAnalogInputTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        anInputMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_ECU1_SEL:
            qDebug() << "Teste de entrada analógica - ECU1!";
            startAnalogInputTest(JigaTestInterface::ECU1_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU2_SEL:
            qDebug() << "Teste de entrada analógica - ECU2!";
                startAnalogInputTest(JigaTestInterface::ECU2_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU3_SEL:
            qDebug() << "Teste de entrada analógica - ECU3!";
            startAnalogInputTest(JigaTestInterface::ECU3_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU4_SEL:
            qDebug() << "Teste de entrada analógica - ECU4!";
            startAnalogInputTest(JigaTestInterface::ECU4_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ALL_SEL:
            qDebug() << "Teste de entrada analógica - todos!";
            startAnalogInputTest(JigaTestInterface::ALL_BOARDS_ID);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectAnalogOutputTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        anOutputMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            anOutputMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::ANALOG_OUTPUT_TEST);
            anOutputMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectCanInitTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        cInitMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_ECU1_SEL:
            qDebug() << "Teste inicialização CAN - ECU1";
            startCanInitTest(JigaTestInterface::ECU1_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU2_SEL:
            qDebug() << "Teste inicialização CAN - ECU2";
            startCanInitTest(JigaTestInterface::ECU2_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU3_SEL:
            qDebug() << "Teste inicialização CAN - ECU3";
            startCanInitTest(JigaTestInterface::ECU3_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU4_SEL:
            qDebug() << "Teste inicialização CAN - ECU4";
            startCanInitTest(JigaTestInterface::ECU4_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ALL_SEL:
            qDebug() << "Teste inicialização CAN - todos";
            startCanInitTest(JigaTestInterface::ALL_BOARDS_ID);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectLoopbackCanTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        cLoopbackMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_ECU1_SEL:
            qDebug() << "Teste loopback CAN - ECU1";
            startCanLoopbackTest(JigaTestInterface::ECU1_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU2_SEL:
            qDebug() << "Teste loopback CAN - ECU2";
            startCanLoopbackTest(JigaTestInterface::ECU2_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU3_SEL:
            qDebug() << "Teste loopback CAN - ECU3";
            startCanLoopbackTest(JigaTestInterface::ECU3_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU4_SEL:
            qDebug() << "Teste loopback CAN - ECU4";
            startCanLoopbackTest(JigaTestInterface::ECU4_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ALL_SEL:
            qDebug() << "Teste loopback CAN - todos";
            startCanLoopbackTest(JigaTestInterface::ALL_BOARDS_ID);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectCan1NetworkTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        c1NetworkMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_CAN1_NETWORK_ECU12_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN1_NETWORK_ECU13_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN1_NETWORK_ECU14_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN1_NETWORK_ECU23_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN1_NETWORK_ECU24_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN1_NETWORK_ECU34_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN1_NETWORK_TEST:
            qDebug() << "Teste da rede CAN1 (todos) selecionado!";
            startCan1NetworkTest(JigaTestInterface::CAN1_NETWORK_TEST);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectCan2NetworkTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        c2NetworkMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_CAN2_NETWORK_ECU23_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN2_NETWORK_ECU24_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_CAN2_NETWORK_ECU34_TEST:
            qDebug() << "Opção não implementada!";
            break;

        case MenuOptionsInterface::OPT_ALL_SEL:
            qDebug() << "Teste da rede CAN2 selecionado!";
            startCan2NetworkTest();
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectLinNetworkTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        lnNetworkMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            lnNetworkMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::LIN_NETWORK_TEST);
            lnNetworkMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}




void JigaView::selectFirmwareUpload() {
    char opt;
    QTextStream input(stdin);

    while (true) {
        ecuUploadMenu->printOptionMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_ECU1_SEL:
            qDebug() << "Atualização de firmware - ECU1";
            selectEcuProcessor(JigaTestInterface::ECU1_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU2_SEL:
            qDebug() << "Atualização de firmware - ECU2";
            selectEcuProcessor(JigaTestInterface::ECU2_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU3_SEL:
            qDebug() << "Atualização de firmware - ECU3";
            selectEcuProcessor(JigaTestInterface::ECU3_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_ECU4_SEL:
            qDebug() << "Atualização de firmware - ECU4";
            selectEcuProcessor(JigaTestInterface::ECU4_BOARD_ID);
            break;

        case MenuOptionsInterface::OPT_MCU1_SEL:
            qDebug() << "Atualização de firmware - MCU1";
            startMcuFirmwareUpload();
            break;

        case MenuOptionsInterface::OPT_ALL_SEL:
            qDebug() << "Atualização de firmware - ECUs";
            selectEcuProcessor(JigaTestInterface::ALL_BOARDS_ID);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectExecuteAllTests()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        mainMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST: {
            // 1 - Teste de comunicação
            commMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::COMMUNICATION_TEST);
            commMenu->printFinishedTestMenu();

            // 2 - Atualização de firmware
            // mcuFmController->executeFirmwareUpload();;

            // 3 - Teste das entradas digitais
            diInputMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::DIGITAL_INPUT_TEST);
            diInputMenu->printFinishedTestMenu();

            // 4 - Teste das entradas analógicas
            anInputMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::ANALOG_INPUT_TEST);
            anInputMenu->printFinishedTestMenu();

            // 5 - Teste das saídas analógicas
            anOutputMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::ANALOG_OUTPUT_TEST);
            anOutputMenu->printFinishedTestMenu();

            // 6 - Teste de inicialização CAN
            cInitMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::CAN_INIT_TEST);
            cInitMenu->printFinishedTestMenu();

            // 7 - Teste de rede loopback CAN
            cLoopbackMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::CAN_LOOPBACK_TEST);
            cLoopbackMenu->printFinishedTestMenu();

            // 8 - Teste de rede CAN1 Network
            c1NetworkMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::CAN1_NETWORK_TEST);
            c1NetworkMenu->printFinishedTestMenu();

            // 9 - Teste de rede CAN2 Network
            c2NetworkMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::CAN2_NETWORK_TEST);
            c2NetworkMenu->printFinishedTestMenu();

            // 10 - Teste de rede LIN Network
            lnNetworkMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::LIN_NETWORK_TEST);
            lnNetworkMenu->printFinishedTestMenu();

            break;
        }
        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectReportTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        repTestMenu->printReportMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_COMMUNICATION_TEST:
            commMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::COMMUNICATION_TEST);
            break;

        case MenuOptionsInterface::OPT_DIGITAL_INPUT_TEST:
            diInputMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::DIGITAL_INPUT_TEST);
            break;

        case MenuOptionsInterface::OPT_ANALOG_INPUT_TEST:
            anInputMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::ANALOG_INPUT_TEST);
            break;

        case MenuOptionsInterface::OPT_ANALOG_OUTPUT_TEST:
            anOutputMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::ANALOG_OUTPUT_TEST);
            break;

        case MenuOptionsInterface::OPT_CAN_INIT_TEST:
            cInitMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN_INIT_TEST);
            break;

        case MenuOptionsInterface::OPT_LOOPBACK_CAN_TEST:
            cLoopbackMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN_LOOPBACK_TEST);
            break;

        case MenuOptionsInterface::OPT_CAN1_NETWORK_TEST:
            c1NetworkMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN1_NETWORK_TEST);
            break;

        case MenuOptionsInterface::OPT_CAN2_NETWORK_TEST:
            c2NetworkMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN2_NETWORK_TEST);
            break;

        case MenuOptionsInterface::OPT_LIN_NETWORK_TEST:
            lnNetworkMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::LIN_NETWORK_TEST);
            break;

        case MenuOptionsInterface::OPT_REPORT_ALL_TEST:
            commMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::COMMUNICATION_TEST);
            diInputMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::DIGITAL_INPUT_TEST);
            anInputMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::ANALOG_INPUT_TEST);
            anOutputMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::ANALOG_OUTPUT_TEST);
            cInitMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN_INIT_TEST);
            cLoopbackMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN_LOOPBACK_TEST);
            c1NetworkMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN1_NETWORK_TEST);
            c2NetworkMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::CAN2_NETWORK_TEST);
            lnNetworkMenu->printReportTestMenu();
            ecuFmController->executeTestReport(JigaTestInterface::LIN_NETWORK_TEST);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectLoadSerialPortTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        loadSerialPortMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            loadSerialPortMenu->printStartedTestMenu();
            ecuFmController->executeFindSerialPortTest();
            loadSerialPortMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}


void JigaView::startCommunicationTest(int boardId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        commMenu->printWarningMessageMenu();
        QString line = input.readLine();
        if (line.isEmpty()) {
            continue;
        }
        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            commMenu->printStartedTestMenu();
            if (boardId == JigaTestInterface::ALL_BOARDS_ID) {
                ecuFmController->executeTest(JigaTestInterface::COMMUNICATION_TEST);
            } else {
                ecuFmController->executeTest(JigaTestInterface::COMMUNICATION_TEST, boardId);
            }
            commMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::startMCUInterfaceTest(int testId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        mcuInterfaceMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            mcuInterfaceMenu->printStartedTestMenu();
            ecuFmController->executeTest(testId, JigaTestInterface::MCU1_BOARD_ID);
            mcuInterfaceMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::startDigitalInputTest(int boardId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        diInputMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
            diInputMenu->printStartedTestMenu();
        case MenuOptionsInterface::OPT_START_TEST:
            if (boardId == JigaTestInterface::ALL_BOARDS_ID) {
                ecuFmController->executeTest(JigaTestInterface::DIGITAL_INPUT_TEST);
            } else {
                ecuFmController->executeTest(JigaTestInterface::DIGITAL_INPUT_TEST, boardId);
            }
            diInputMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::startAnalogInputTest(int boardId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        anInputMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            anInputMenu->printStartedTestMenu();
            if (boardId == JigaTestInterface::ALL_BOARDS_ID) {
                ecuFmController->executeTest(JigaTestInterface::ANALOG_INPUT_TEST);
            } else {
                ecuFmController->executeTest(JigaTestInterface::ANALOG_INPUT_TEST, boardId);
            }
            anInputMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::startCan1NetworkTest(int testId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        c1NetworkMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            c1NetworkMenu->printStartedTestMenu();
            ecuFmController->executeTest(testId);
            c1NetworkMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}


void JigaView::startCanLoopbackTest(int boardId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        cLoopbackMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            cLoopbackMenu->printStartedTestMenu();
            if (boardId == JigaTestInterface::ALL_BOARDS_ID) {
                ecuFmController->executeTest(JigaTestInterface::CAN_LOOPBACK_TEST);
            } else {
                ecuFmController->executeTest(JigaTestInterface::CAN_LOOPBACK_TEST, boardId);
            }
            cLoopbackMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::startCan2NetworkTest()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        c2NetworkMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            c2NetworkMenu->printStartedTestMenu();
            ecuFmController->executeTest(JigaTestInterface::CAN2_NETWORK_TEST);
            c2NetworkMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}


void JigaView::startMcuFirmwareUpload()
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        mcuUploadMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_SERIAL_PROG:
            qDebug() << "Opção não implementada!";
            return;

        case MenuOptionsInterface::OPT_USB_PROG:
            mcuUploadMenu->printStartedTestMenu();
            mcuFmController->executeFirmwareUpload(JigaTestInterface::USB_PROG_ID);
            mcuUploadMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::startEcuFirmwareUpload(int boardId, int processorId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        ecuUploadMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            ecuUploadMenu->printStartedTestMenu();
            ecuFmController->executeFirmwareUpload(boardId, processorId);
            ecuUploadMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::startCanInitTest(int boardId)
{
    char opt;
    QTextStream input(stdin);

    while (true) {
        cInitMenu->printWarningMessageMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_START_TEST:
            cInitMenu->printStartedTestMenu();
            if (boardId == JigaTestInterface::ALL_BOARDS_ID) {
                ecuFmController->executeTest(JigaTestInterface::CAN_INIT_TEST);
            } else {
                ecuFmController->executeTest(JigaTestInterface::CAN_INIT_TEST, boardId);
            }
            cInitMenu->printFinishedTestMenu();
            return;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

void JigaView::selectEcuProcessor(int boardId) {
    char opt;
    QTextStream input(stdin);

    while (true) {
        ecuUploadMenu->printEcuProcessorMenu();
        QString line = input.readLine();

        if (line.isEmpty()) {
            continue;
        }

        opt = line[0].toLatin1();

        switch(opt) {
        case MenuOptionsInterface::OPT_ATMEGA328P_OLD:
            qDebug() << "Processor ATmega328P (Old bootloader) selecionado!";
            startEcuFirmwareUpload(boardId, JigaTestInterface::ECU_OLD_BOOTLOADER);
            break;

        case MenuOptionsInterface::OPT_ATMEGA328P:
            qDebug() << "ECU Processor ATmega328P selecionado!";
            startEcuFirmwareUpload(boardId, JigaTestInterface::ECU_NEW_BOOTLOADER);
            break;

        case 'r':
            return;

        default:
            qDebug() << "Opção inválida!";
            break;
        }
    }
}

