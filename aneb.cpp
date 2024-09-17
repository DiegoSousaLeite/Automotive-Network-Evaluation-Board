#include "aneb.h"
#include "ui_aneb.h"
#include "DashboardWidget.h"
#include <QMap>

ANEB* ANEB::instance = nullptr;

ANEB::ANEB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ANEB)
{
    ui->setupUi(this);
    console1 = ui->console;
    console2 = ui->console_2;
    console3 = ui->console_3;
    console4 = ui->console_4;
    console5 = ui->console_5;
    console6 = ui->console_6;
    console7 = ui->console_7;
    console8 = ui->console_8;
    console9 = ui->console_9;
    console10 = ui->console_10;
    console11 = ui->console_11;
    console12 = ui->console_12;
    qInstallMessageHandler(myMessageOutput);  // Instala o manipulador de log personalizado

    instance = this;

    // Inicialização
    dashboardWidget = new DashboardWidget();

    // Verifique se dashPage tem um layout
    if (ui->dashPage->layout() == nullptr) {
        // Crie um layout e defina-o para dashPage se não tiver um
        QVBoxLayout *layout = new QVBoxLayout(ui->dashPage);
        ui->dashPage->setLayout(layout);
    }

    // Adicione o dashboardWidget ao layout da dashPage
    ui->dashPage->layout()->addWidget(dashboardWidget);
    dashboardWidget->hide();

    // Conecta os botões de dashboard a slots que alteram a página
    connect(ui->dashButton, &QPushButton::clicked, this, [this]() {onChangePage(2,4);});
    connect(ui->dashButton2, &QPushButton::clicked, this, [this]() {onChangePage(2,4);});

    // Esconde o widget de ícones
    ui->iconOnlyWidget->hide();

    // Inicializa o QStackedWidget para a primeira página
    ui->stackedWidgetMainPages->setCurrentIndex(0);
    ui->stackedWidgetCommTest->setCurrentIndex(0);

    // Conecta os botões de limpar console ao slot de limpeza
    connect(ui->clearButton, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_2, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_3, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_4, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_6, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_7, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_8, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_9, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_10, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_11, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_12, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_13, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);

    // Conecta sinais dos botões aos slots correspondentes para mudança de página e execução de testes de comunicação
    connect(ui->commButton, &QPushButton::clicked, this, [this]() {onChangePage(0,0);});
    connect(ui->commButton2, &QPushButton::clicked, this, [this]() {onChangePage(0,0);});

    connect(ui->testComm, &QPushButton::clicked, this, [this]() {onChangePage(1,0);});
    connect(ui->ecu1, &QPushButton::clicked, this, [this]() {onExecuteTest(0,JigaTestInterface::ECU1_BOARD_ID);});
    connect(ui->ecu2, &QPushButton::clicked, this, [this]() {onExecuteTest(0,JigaTestInterface::ECU2_BOARD_ID);});
    connect(ui->ecu3, &QPushButton::clicked, this, [this]() {onExecuteTest(0,JigaTestInterface::ECU3_BOARD_ID);});
    connect(ui->ecu4, &QPushButton::clicked, this, [this]() {onExecuteTest(0,JigaTestInterface::ECU4_BOARD_ID);});
    connect(ui->mcu1, &QPushButton::clicked, this, [this]() {onExecuteTest(0,JigaTestInterface::MCU1_BOARD_ID);});
    connect(ui->todos, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::ALL_BOARDS_ID);});

    connect(ui->testCAN1, &QPushButton::clicked, this, [this]() {onChangePage(1,1);});
    connect(ui->startButton, &QPushButton::clicked,this, [this]() {onExecuteTest(1,JigaTestInterface::CAN1_NETWORK_TEST);});

    connect(ui->testCAN2, &QPushButton::clicked, this, [this]() {onChangePage(1,2);});
    connect(ui->startButton_2, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::CAN2_NETWORK_TEST);});

    connect(ui->testInit, &QPushButton::clicked, this, [this]() {onChangePage(1,3);});
    connect(ui->ecu1Init, &QPushButton::clicked, this, [this]() {onExecuteTest(2,JigaTestInterface::ECU1_BOARD_ID);});
    connect(ui->ecu2Init, &QPushButton::clicked, this, [this]() {onExecuteTest(2,JigaTestInterface::ECU2_BOARD_ID);});
    connect(ui->ecu3Init, &QPushButton::clicked, this, [this]() {onExecuteTest(2,JigaTestInterface::ECU3_BOARD_ID);});
    connect(ui->ecu4Init, &QPushButton::clicked, this, [this]() {onExecuteTest(2,JigaTestInterface::ECU4_BOARD_ID);});
    connect(ui->mcu1Init, &QPushButton::clicked, this, [this]() {onExecuteTest(2,JigaTestInterface::MCU1_BOARD_ID);});
    connect(ui->todosInit, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::CAN_INIT_TEST);});

    connect(ui->testLIN, &QPushButton::clicked, this, [this]() {onChangePage(1,4);});
    connect(ui->startButton_4, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::LIN_NETWORK_TEST);});

    connect(ui->testLoop, &QPushButton::clicked,this, [this]() {onChangePage(1,5);});
    connect(ui->ecu1Loop, &QPushButton::clicked, this, [this]() {onExecuteTest(3,JigaTestInterface::ECU1_BOARD_ID);});
    connect(ui->ecu2Loop, &QPushButton::clicked, this, [this]() {onExecuteTest(3,JigaTestInterface::ECU2_BOARD_ID);});
    connect(ui->ecu3Loop, &QPushButton::clicked, this, [this]() {onExecuteTest(3,JigaTestInterface::ECU3_BOARD_ID);});
    connect(ui->ecu4Loop, &QPushButton::clicked, this, [this]() {onExecuteTest(3,JigaTestInterface::ECU4_BOARD_ID);});
    connect(ui->mcu1Loop, &QPushButton::clicked, this, [this]() {onExecuteTest(3,JigaTestInterface::MCU1_BOARD_ID);});
    connect(ui->todosLoop, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::CAN_LOOPBACK_TEST);});

    // Conecta sinais dos botões aos slots correspondentes para mudança de página e execução de testes de entrada de saída
    connect(ui->ioButton, &QPushButton::clicked,this, [this]() {onChangePage(0,1);});
    connect(ui->ioButton2, &QPushButton::clicked,this, [this]() {onChangePage(0,1);});

    connect(ui->testInDig, &QPushButton::clicked, this, [this]() {onChangePage(3,0);});
    connect(ui->ecu1InDig, &QPushButton::clicked, this, [this]() {onExecuteTest(4,JigaTestInterface::ECU1_BOARD_ID);});
    connect(ui->ecu2InDig, &QPushButton::clicked, this, [this]() {onExecuteTest(4,JigaTestInterface::ECU2_BOARD_ID);});
    connect(ui->ecu3InDig, &QPushButton::clicked, this, [this]() {onExecuteTest(4,JigaTestInterface::ECU3_BOARD_ID);});
    connect(ui->ecu4InDig, &QPushButton::clicked, this, [this]() {onExecuteTest(4,JigaTestInterface::ECU4_BOARD_ID);});
    connect(ui->mcu1InDig, &QPushButton::clicked, this, [this]() {onExecuteTest(4,JigaTestInterface::MCU1_BOARD_ID);});
    connect(ui->todosInDig, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::DIGITAL_INPUT_TEST);});

    connect(ui->testInAn, &QPushButton::clicked, this, [this]() {onChangePage(3,1);});
    connect(ui->ecu1InAn, &QPushButton::clicked, this, [this]() {onExecuteTest(5,JigaTestInterface::ECU1_BOARD_ID);});
    connect(ui->ecu2InAn, &QPushButton::clicked, this, [this]() {onExecuteTest(5,JigaTestInterface::ECU2_BOARD_ID);});
    connect(ui->ecu3InAn, &QPushButton::clicked, this, [this]() {onExecuteTest(5,JigaTestInterface::ECU3_BOARD_ID);});
    connect(ui->ecu4InAn, &QPushButton::clicked, this, [this]() {onExecuteTest(5,JigaTestInterface::ECU4_BOARD_ID);});
    connect(ui->mcu1InAn, &QPushButton::clicked, this, [this]() {onExecuteTest(5,JigaTestInterface::MCU1_BOARD_ID);});
    connect(ui->todosInAn, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::ANALOG_INPUT_TEST);});

    connect(ui->testOutAn, &QPushButton::clicked, this, [this]() {onChangePage(3,2);});
    connect(ui->startButton_5, &QPushButton::clicked, this, [this]() {onExecuteTest(1,JigaTestInterface::ANALOG_OUTPUT_TEST);});

    // Conecta sinais dos botões aos slots correspondentes para mudança de página e execução de outros testes
    connect(ui->otherButton, &QPushButton::clicked, this, [this]() {onChangePage(0,2);});
    connect(ui->otherButton2, &QPushButton::clicked, this, [this]() {onChangePage(0,2);});

    connect(ui->testInterface, &QPushButton::clicked, this, [this]() {onChangePage(4,0);});
    connect(ui->idenPort, &QPushButton::clicked, this, [this]() {onExecuteTest(6,JigaTestInterface::MCU_IDENT_PORT_TEST);});
    connect(ui->redeCAN1, &QPushButton::clicked, this, [this]() {onExecuteTest(6,JigaTestInterface::MCU_SEL_CANBUS1_TEST);});
    connect(ui->redeCAN2, &QPushButton::clicked, this, [this]() {onExecuteTest(6,JigaTestInterface::MCU_SEL_CANBUS2_TEST);});
    connect(ui->onReset, &QPushButton::clicked, this, [this]() {onExecuteTest(6,JigaTestInterface::MCU_RST_ACT_TEST);});
    connect(ui->offReset, &QPushButton::clicked, this, [this]() {onExecuteTest(6,JigaTestInterface::MCU_RST_DAC_TEST);});
    connect(ui->onResetTimeout, &QPushButton::clicked, this, [this]() {onExecuteTest(6,JigaTestInterface::MCU_RST_ATT_TEST);});

    connect(ui->testAuto, &QPushButton::clicked, this, [this]() {onChangePage(4,1);});
    connect(ui->startButton_6,&QPushButton::clicked, this, [this]() {onExecuteTest(7,0);});

    connect(ui->emitRelatorio, &QPushButton::clicked, this, [this]() {onChangePage(4,2);});
    connect(ui->commRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_COMMUNICATION_TEST);});
    connect(ui->inDigRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_DIGITAL_INPUT_TEST);});
    connect(ui->inAnRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_ANALOG_INPUT_TEST);});
    connect(ui->outAnRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_ANALOG_OUTPUT_TEST);});
    connect(ui->initRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_CAN_INIT_TEST);});
    connect(ui->loopRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_LOOPBACK_CAN_TEST);});
    connect(ui->can1Rela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_CAN1_NETWORK_TEST);});
    connect(ui->can2Rela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_CAN2_NETWORK_TEST);});
    connect(ui->linRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_LIN_NETWORK_TEST);});
    connect(ui->allRela, &QPushButton::clicked, this, [this]() {onReportTest(MenuOptionsInterface::OPT_REPORT_ALL_TEST);});



    // Configurando como checado por padrão
    ui->commButton2->setChecked(true);
    ui->testComm->setChecked(true);
    ui->testInDig->setChecked(true);
    ui->testInterface->setChecked(true);
}

ANEB::~ANEB()
{
    instance = nullptr;
    delete ui;
}

// Define o controlador de quadro ECU
void ANEB::setEcuFrameController(EcuFrameController *controller)
{
    ecuFmController = controller;
}

// Define o controlador de quadro MCU
void ANEB::setMcuFrameController(McuFrameController *controller)
{
    mcuFmController = controller;
}

// Inicializa o dispositivo e os componentes relacionados
void ANEB::initializeDevice() {
    qDebug() << "Starting device initialization...";

    // Inicializando PersistenceController
    qDebug() << "Initializing PersistenceController...";
    PersistenceController* psController = PersistenceController::getInstance();
    if (!psController) {
        qDebug() << "Failed to get PersistenceController instance";
        return;
    }

    // Cria uma instância de SystemDefinition e imprime propriedades do sistema
    qDebug() << "Creating SystemDefinition instance...";
    SystemDefinition sDefinition;
    qDebug() << "Printing System Properties...";
    sDefinition.printSystemProperties();

    // Verifica se o programador USB está conectado
    bool deviceFound = psController->loadUsbProgrammer();
    if (!deviceFound) {
        qDebug() << "USBASC not found!";
    } else {
        qDebug() << "USBASC Found";
        //        qDebug() << "Serial Number =" << psController->getUsbDeviceSerialNumber();
        //        qDebug() << "Product ID =" << psController->getUsbDeviceProductString();
        //        qDebug() << "Manufacturer =" << psController->getUsbDeviceManufacturerString();
    }

    qDebug() << "Device initialization completed.";
}

// Altera a página no QStackedWidget com base no índice fornecido
void ANEB::onChangePage(int page, int pageIndex)
{
    switch(page) {
    // Menu Principal
    case 0:
        ui->stackedWidgetMainPages->setCurrentIndex(pageIndex);
        break;
    // Comunicação
    case 1:
        ui->stackedWidgetCommTest->setCurrentIndex(pageIndex);
        break;
    // DashBoard
    case 2:
        ui->stackedWidgetMainPages->setCurrentIndex(pageIndex);
        dashboardWidget->show(); // Mostra o DashBoard
        break;
    //IO Test
    case 3:
        ui->stackedWidgetIoTest->setCurrentIndex(pageIndex);
        break;
    //Other Test
    case 4:
        ui->stackedWidgetOther->setCurrentIndex(pageIndex);
        break;
    default:
        qWarning() << "Unknown page index:" << page;
        break;
    }
}

// Executa um teste com base no tipo e ID fornecidos
void ANEB::onExecuteTest(int tipo, int id)
{
    switch (tipo) {
    case 0:
        ecuFmController->executeTest(JigaTestInterface::COMMUNICATION_TEST,id);
        break;
    case 1:
        ecuFmController->executeTest(id);
        break;
    case 2:
        ecuFmController->executeTest(JigaTestInterface::CAN_INIT_TEST,id);
        break;
    case 3:
        ecuFmController->executeTest(JigaTestInterface::CAN_LOOPBACK_TEST,id);
        break;
    case 4:
        ecuFmController->executeTest(JigaTestInterface::DIGITAL_INPUT_TEST,id);
        break;
    case 5:
        ecuFmController->executeTest(JigaTestInterface::ANALOG_INPUT_TEST, id);
        break;
    case 6:
        ecuFmController->executeTest(id,JigaTestInterface::MCU1_BOARD_ID);
        break;
    case 7:
        ecuFmController->executeTest(JigaTestInterface::COMMUNICATION_TEST);
        ecuFmController->executeTest(JigaTestInterface::DIGITAL_INPUT_TEST);
        ecuFmController->executeTest(JigaTestInterface::ANALOG_INPUT_TEST);
        ecuFmController->executeTest(JigaTestInterface::ANALOG_OUTPUT_TEST);
        ecuFmController->executeTest(JigaTestInterface::CAN_INIT_TEST);
        ecuFmController->executeTest(JigaTestInterface::CAN_LOOPBACK_TEST);
        ecuFmController->executeTest(JigaTestInterface::CAN1_NETWORK_TEST);
        ecuFmController->executeTest(JigaTestInterface::CAN2_NETWORK_TEST);
        ecuFmController->executeTest(JigaTestInterface::LIN_NETWORK_TEST);
        break;
    default:
        break;
    }
}

void ANEB::onReportTest(int tipo)
{

    if (tipo == MenuOptionsInterface::OPT_REPORT_ALL_TEST) {
        // Executa todos os testes
        ecuFmController->executeTestReport(JigaTestInterface::COMMUNICATION_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::DIGITAL_INPUT_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::ANALOG_INPUT_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::ANALOG_OUTPUT_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::CAN_INIT_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::CAN_LOOPBACK_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::CAN1_NETWORK_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::CAN2_NETWORK_TEST);
        ecuFmController->executeTestReport(JigaTestInterface::LIN_NETWORK_TEST);
    } else {
        // Executa o teste correspondente ao tipo
        switch (tipo) {
        case MenuOptionsInterface::OPT_COMMUNICATION_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::COMMUNICATION_TEST);
            break;
        case MenuOptionsInterface::OPT_DIGITAL_INPUT_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::DIGITAL_INPUT_TEST);
            break;
        case MenuOptionsInterface::OPT_ANALOG_INPUT_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::ANALOG_INPUT_TEST);
            break;
        case MenuOptionsInterface::OPT_ANALOG_OUTPUT_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::ANALOG_OUTPUT_TEST);
            break;
        case MenuOptionsInterface::OPT_CAN_INIT_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::CAN_INIT_TEST);
            break;
        case MenuOptionsInterface::OPT_LOOPBACK_CAN_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::CAN_LOOPBACK_TEST);
            break;
        case MenuOptionsInterface::OPT_CAN1_NETWORK_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::CAN1_NETWORK_TEST);
            break;
        case MenuOptionsInterface::OPT_CAN2_NETWORK_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::CAN2_NETWORK_TEST);
            break;
        case MenuOptionsInterface::OPT_LIN_NETWORK_TEST:
            ecuFmController->executeTestReport(JigaTestInterface::LIN_NETWORK_TEST);
            break;
        default:
            break;
        }
    }
}


// Limpa o console quando um botão de limpeza é pressionado
void ANEB::onCleanConsoleButtonClicked() {
    QObject *senderObj = sender(); // Obter o objeto que emitiu o sinal

    if (senderObj == ui->clearButton) {
        // Se o botão "clearButton" foi clicado, limpar o console 1
        if (console1) {
            console1->clear();
        }
    } else if (senderObj == ui->clearButton_2) {
        // Se o botão "clearButton_2" foi clicado, limpar o console 2
        if (console2) {
            console2->clear();
        }
    } else if (senderObj == ui->clearButton_3) {
        // Se o botão "clearButton_3" foi clicado, limpar o console 3
        if (console3) {
            console3->clear();
        }
    } else if (senderObj == ui->clearButton_4) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console4) {
            console4->clear();
        }
    } else if (senderObj == ui->clearButton_6) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console5) {
            console5->clear();
        }
    } else if (senderObj == ui->clearButton_7) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console6) {
            console6->clear();
        }
    } else if (senderObj == ui->clearButton_8) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console7) {
            console7->clear();
        }
    } else if (senderObj == ui->clearButton_9) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console8) {
            console8->clear();
        }
    } else if (senderObj == ui->clearButton_10) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console9) {
            console9->clear();
        }
    } else if (senderObj == ui->clearButton_11) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console10) {
            console10->clear();
        }
    } else if (senderObj == ui->clearButton_12) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console11) {
            console11->clear();
        }
    } else if (senderObj == ui->clearButton_13) {
        // Se o botão "clearButton_4" foi clicado, limpar o console 4
        if (console12) {
            console12->clear();
        }
    }

}

//// Manipulador de saída de mensagens personalizado que exibe mensagens formatadas nos consoles apropriados
//void ANEB::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    Q_UNUSED(context);

//    // Formatar a mensagem de acordo com o tipo
//    QString formattedMessage;
//    switch (type) {
//    case QtDebugMsg:
//        formattedMessage = QString("<b>Debug:</b> %1").arg(msg);
//        break;
//    case QtInfoMsg:
//        formattedMessage = QString("<b>Info:</b> %1").arg(msg);
//        break;
//    case QtWarningMsg:
//        formattedMessage = QString("<b>Warning:</b> %1").arg(msg);
//        break;
//    case QtCriticalMsg:
//        formattedMessage = QString("<b>Critical:</b> %1").arg(msg);
//        break;
//    case QtFatalMsg:
//        formattedMessage = QString("<b>Fatal:</b> %1").arg(msg);
//        abort();  // Fecha o programa
//    }

//    // Usar o ponteiro da instância para acessar `ui`
//    if (instance) {
//        // Selecionar o console apropriado com base na página ativa
//        QTextBrowser* targetConsole = nullptr;

//        if (instance->ui->stackedWidgetCommTest->currentIndex() == 0) {
//            targetConsole = instance->console1;
//        } else if (instance->ui->stackedWidgetCommTest->currentIndex() == 1) {
//            targetConsole = instance->console2;
//        } else if (instance->ui->stackedWidgetCommTest->currentIndex() == 2) {
//            targetConsole = instance->console3;
//        } else if (instance->ui->stackedWidgetCommTest->currentIndex() == 3) {
//            targetConsole = instance->console4;
//        } else if (instance->ui->stackedWidgetCommTest->currentIndex() == 4) {
//            targetConsole = instance->console5;
//        } else if (instance->ui->stackedWidgetCommTest->currentIndex() == 5) {
//            targetConsole = instance->console6;
//        }

//        // Adicionar a mensagem ao console selecionado
//        if (targetConsole) {
//            targetConsole->append(formattedMessage);
//        }
//    }
//}
// Manipulador de saída de mensagens personalizado que exibe mensagens formatadas nos consoles apropriados em tempo real
void ANEB::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    // Formata a mensagem de acordo com o tipo
    QString formattedMessage;
    switch (type) {
    case QtDebugMsg:
        formattedMessage = QString("<b>Debug:</b> %1").arg(msg);
        break;
    case QtInfoMsg:
        formattedMessage = QString("<b>Info:</b> %1").arg(msg);
        break;
    case QtWarningMsg:
        formattedMessage = QString("<b>Warning:</b> %1").arg(msg);
        break;
    case QtCriticalMsg:
        formattedMessage = QString("<b>Critical:</b> %1").arg(msg);
        break;
    case QtFatalMsg:
        formattedMessage = QString("<b>Fatal:</b> %1").arg(msg);
        abort();  // Fecha o programa
    }

    // Usa o ponteiro da instância para acessar `ui`
    if (instance) {
        // Seleciona o console apropriado com base na página ativa
        QTextBrowser* targetConsole = nullptr;

        if (instance->ui->stackedWidgetCommTest->isVisible()) {
            // Seleciona o console baseado no índice do stackedWidgetCommTest
            switch (instance->ui->stackedWidgetCommTest->currentIndex()) {
            case 0:
                targetConsole = instance->console1;
                break;
            case 1:
                targetConsole = instance->console2;
                break;
            case 2:
                targetConsole = instance->console3;
                break;
            case 3:
                targetConsole = instance->console4;
                break;
            case 4:
                targetConsole = instance->console5;
                break;
            case 5:
                targetConsole = instance->console6;
                break;
            }
        } else if (instance->ui->stackedWidgetIoTest->isVisible()) {
            // Seleciona o console baseado no índice do stackedWidgetIoTest
            switch (instance->ui->stackedWidgetIoTest->currentIndex()) {
            case 0:
                targetConsole = instance->console7;
                break;
            case 1:
                targetConsole = instance->console8;
                break;
            case 2:
                targetConsole = instance->console9;
                break;
            default:
                break;
            }

        } else if (instance->ui->stackedWidgetOther->isVisible()) {
            // Seleciona o console baseado no índice do stackedWidgetOther
            switch (instance->ui->stackedWidgetOther->currentIndex()) {
            case 0:
                targetConsole = instance->console10;
                break;
            case 1:
                targetConsole = instance->console11;
                break;
            case 2:
                targetConsole = instance->console12;
                break;
            default:
                break;
            }

        }


        // Adiciona a mensagem ao console selecionado
        if (targetConsole) {
            targetConsole->append(formattedMessage);
            QCoreApplication::processEvents();  // Processa eventos pendentes
        }
    }
}

