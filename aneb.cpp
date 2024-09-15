#include "aneb.h"
#include "ui_aneb.h"
#include "DashboardWidget.h"

ANEB* ANEB::instance = nullptr;

ANEB::ANEB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ANEB)
{
    ui->setupUi(this);
    console1 = ui->console;
    console2 = ui->console_2;
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
    connect(ui->dashButton, &QPushButton::clicked, this, [this]() {onChangePage(2,1);});
    connect(ui->dashButton2, &QPushButton::clicked, this, [this]() {onChangePage(2,1);});

    // Esconde o widget de ícones
    ui->iconOnlyWidget->hide();

    // Inicializa o QStackedWidget para a primeira página
    ui->stackedWidgetMainPages->setCurrentIndex(0);
    ui->stackedWidgetCommTest->setCurrentIndex(0);

    // Conecta os botões de limpar console ao slot de limpeza
    connect(ui->clearButton, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);
    connect(ui->clearButton_2, &QPushButton::clicked, this, &ANEB::onCleanConsoleButtonClicked);

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
    connect(ui->startButton, &QPushButton::clicked,this, [this]() {onExecuteTest(0,JigaTestInterface::CAN1_NETWORK_TEST);});

    // Configurando como checado por padrão
    ui->commButton2->setChecked(true);
    ui->testComm->setChecked(true);
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
    default:
        break;
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
    }
}

// Manipulador de saída de mensagens personalizado que exibe mensagens formatadas nos consoles apropriados
void ANEB::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    // Formatar a mensagem de acordo com o tipo
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

    // Usar o ponteiro da instância para acessar `ui`
    if (instance) {
        // Selecionar o console apropriado com base na página ativa
        QTextBrowser* targetConsole = nullptr;

        if (instance->ui->stackedWidgetCommTest->currentIndex() == 0) {
            targetConsole = instance->console1;
        } else if (instance->ui->stackedWidgetCommTest->currentIndex() == 1) {
            targetConsole = instance->console2;
        }

        // Adicionar a mensagem ao console selecionado
        if (targetConsole) {
            targetConsole->append(formattedMessage);
        }
    }
}
