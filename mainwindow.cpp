#include "mainwindow.h"
#include <QStackedWidget>
#include "virtual_io.h"
#include <QFileDialog>
#include <QTextBrowser>
#include <QMessageBox>
#include <QList>
#include <QSerialPortInfo>
#include <QCursor>
#include <QThread>


// Constructor for MainWindow class
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    setFixedSize(1071, 600);
    ui->setupUi(this); // Setup the UI elements based on the design from Qt Designer
    staticConsole = ui->console;  // Inicializa o console estático
    setupButtonStyles(); // Function call to centralize the style configuration and page switching setup
    qInstallMessageHandler(myMessageOutput);  // Instala o manipulador de log personalizado
    updateComboBoxCommPortList(); // Atualiza a lista de portas seriais na inicialização

    ecuFmController = new EcuFrameController(this); // Inicializa o controlador

    // Create the Virtual_IO widget, set its parent to ui->pageVirtual for proper hierarchy
    virtualIOWidget = new Virtual_IO(ui->pageVirtual);
    virtualIOWidget->setGeometry(QRect(0,-40,1081,491)); // Adjust the size to fit the parent widget
    virtualIOWidget->hide(); // Hide the widget initially until the respective button is clicked

    // Connect the 'virtualButton' click to the function that shows the Virtual_IO page
    connect(ui->virtualButton, &QPushButton::clicked, this, &MainWindow::showVirtualIO);

    connect(ui->firmwareUpdateButton, &QPushButton::clicked, this, &MainWindow::onFirmwareUpdateButtonClicked);
    connect(ui->cleanConsoleButton, &QPushButton::clicked,this,&MainWindow::onCleanConsoleButtonClicked);
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::updateComboBoxCommPortList);
    connect(ui->masterResetButton, &QPushButton::clicked, this, &MainWindow::onMasterResetButtonClicked);
    connect(ui->ecu3Button, &QPushButton::clicked,this, &MainWindow::onECU3CANBusButtonClicked);
    connect(ui->ecu4Button, &QPushButton::clicked,this, &MainWindow::onECU4CANBusButtonClicked);
    connect(ui->cameraButton, &QPushButton::clicked, this, &MainWindow::onLoadWebCamButtonClicked);



    // Apply an active style to the firmware button, as it's the main/start page
    QString activeButtonStyle = "QPushButton { "
                                "background-color: rgba(0, 0, 255, 128); "
                                "border-radius: 15px; "
                                "}";
    ui->firmwareButton->setStyleSheet(activeButtonStyle);
    ui->stackedWidget->setCurrentWidget(ui->pageFirmware); // Set the initial visible page to firmware

}
QTextBrowser* MainWindow::staticConsole = nullptr;

// Destructor for MainWindow class
MainWindow::~MainWindow() {
    staticConsole = nullptr;
    delete ui; // Clean up the Ui::MainWindow object when the MainWindow object is destroyed
}

void MainWindow::initializeDevice() {
    qDebug() << "Starting device initialization...";

    // Inicializando PersistenceController
    qDebug() << "Initializing PersistenceController...";
    PersistenceController* psController = PersistenceController::getInstance();
    if (!psController) {
        qDebug() << "Failed to get PersistenceController instance";
        return;
    }

    qDebug() << "Creating SystemDefinition instance...";
    SystemDefinition sDefinition;
    qDebug() << "Printing System Properties...";
    sDefinition.printSystemProperties();

    bool deviceFound = psController->loadUsbProgrammer();
    if (!deviceFound) {
        qDebug() << "USBASC not found!";
    } else {
        qDebug() << "USBASC Found";
//        qDebug() << "Serial Number =" << psController->getUsbDeviceSerialNumber();
//        qDebug() << "Product ID =" << psController->getUsbDeviceProductString();
//        qDebug() << "Manufacturer =" << psController->getUsbDeviceManufacturerString();
    }

    // Inicializando McuBusinessController
//    qDebug() << "Initializing McuBusinessController...";
//    McuBusinessController mcuBController;
//    mcuBController.setPersistenceController(psController);

//    bool progLoaded = mcuBController.loadProgrammer(JigaTestInterface::SERIAL_PROG_ID);
//    if (progLoaded) {
//        qDebug() << "Programmer is loaded!";
//        mcuBController.uploadFirmware(JigaTestInterface::SERIAL_PROG_ID);
//    } else {
//        qDebug() << "Programmer is not loaded!";
//    }

//    QThread::sleep(3); // Simulating delay

    // Inicializando EcuBusinessController
//    qDebug() << "Initializing EcuBusinessController...";
//    EcuBusinessController ecuBController;
//    ecuBController.setPersistenceController(psController);

//    int portFounds = psController->findSerialCommPorts();
//    qDebug() << "Number of ports =" << portFounds;

//    for (int i = 0; i < portFounds; ++i) {
//        int index = psController->getCommPortFound(i);
//        qDebug() << "[" << i << "] : (" << psController->getPortDescription(index) << ") : ("
//                 << psController->getDescriptivePortName(index) << ")";
//    }

//    QThread::sleep(3); // Simulating delay

    qDebug() << "Device initialization completed.";
}




// Function to set up the styles and behaviors for navigation buttons
void MainWindow::setupButtonStyles() {
    QString activeButtonStyle = "QPushButton { "
                                "background-color: rgba(0, 0, 255, 128); "
                                "border-radius: 15px; "
                                "}";

    QString defaultButtonStyle = "QPushButton { background-color: none; }";

    // Helper lambda function to connect each button to its respective slot while adjusting the style
    auto connectButton = [this, defaultButtonStyle, activeButtonStyle](QPushButton *button, QWidget *page) {
        connect(button, &QPushButton::clicked, this, [this, button, page, activeButtonStyle, defaultButtonStyle]() {
            ui->stackedWidget->setCurrentWidget(page); // Change the current widget to the one associated with the button
            resetButtonStyles(defaultButtonStyle); // Reset all button styles to default
            button->setStyleSheet(activeButtonStyle); // Apply the active style to the clicked button
        });
    };

    // Connect each button to the setup function with its respective page
    connectButton(ui->firmwareButton, ui->pageFirmware);
    connectButton(ui->virtualButton, ui->pageVirtual);
    connectButton(ui->dashboardButton, ui->pageDashboard);
}

// Function to reset the styles of all navigation buttons to default
void MainWindow::resetButtonStyles(const QString &defaultStyle) {
    ui->firmwareButton->setStyleSheet(defaultStyle);
    ui->virtualButton->setStyleSheet(defaultStyle);
    ui->dashboardButton->setStyleSheet(defaultStyle);
}

// Function to display the Virtual_IO widget when its respective button is clicked
void MainWindow::showVirtualIO() {
    ui->stackedWidget->setCurrentWidget(ui->pageVirtual);
    virtualIOWidget->show(); // Show the Virtual_IO widget

}

// Simplified navigation functions to show respective pages (not used in the current setup but available)
void MainWindow::pageFirmware() {
    ui->stackedWidget->setCurrentWidget(ui->pageFirmware);
}

void MainWindow::pageVirtual() {
    ui->stackedWidget->setCurrentWidget(ui->pageVirtual);
}

void MainWindow::updateComboBoxCommPortList() {
    ui->comboBox->clear(); // Limpa o comboBox para remover itens antigos

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    // Adiciona portas atualizadas ao comboBox
    for (const QSerialPortInfo &port : ports) {
        QString portDescription = QString("[%1] %2: %3 : %4")
                                      .arg(QString::number(ui->comboBox->count()))
                                      .arg(port.portName())
                                      .arg(port.description())
                                      .arg(port.serialNumber());


        ui->comboBox->addItem(portDescription);

    }
    qDebug() << "ECU Serial Port atualizadas";
}


void MainWindow::onFirmwareUpdateButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Firmware File"), "",
                                                    tr("Firmware Files (*.hex)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Error"), tr("Cannot open the file."));
            return;
        }
        qDebug() << "Arquivo selecionado:" << fileName;
    }
}

void MainWindow::onMasterResetButtonClicked()
{
    // Verifica se o cursor atual é um cursor de espera
    if (this->cursor().shape() == Qt::WaitCursor) {
        QApplication::beep();  // Emite um beep sonoro
        return;
    }
    // Define o cursor para o estado de espera
    this->setCursor(Qt::WaitCursor);

    // Verifica se o controlador 'ecuFmController' foi inicializado
    if (!ecuFmController) {
        qDebug() << "Erro: ecuFmController não inicializado!";
        this->setCursor(Qt::ArrowCursor);  // Retorna o cursor ao normal
        return;
    }

    // Cria uma nova thread para executar o reset de forma assíncrona
    QThread* workerThread = QThread::create([=] {
        QString line = ">> Master reset inicializado...";

        // Verifica se o console estático está inicializado
        if (staticConsole) {
            staticConsole->append(line);  // Adiciona a linha ao console
        } else {
            qDebug() << "Erro: staticConsole não inicializado!";
        }

        // Executa o teste de reset no controlador 'ecuFmController'
        if (ecuFmController) {
            //ESSA É A CERTA
            //ecuFmController->executeTest(JigaTestInterface::MCU_RST_ATT_TEST, JigaTestInterface::MCU1_BOARD_ID);
            //PARA TESTES NO MAC
            ecuFmController->executeTest(JigaTestInterface::MCU_RST_ATT_TEST, JigaTestInterface::ECU4_BOARD_ID);
        } else {
            qDebug() << "Erro: ecuFmController não inicializado dentro do thread!";  // Imprime mensagem de erro
        }

        qDebug() << "Passou o executeTest";

        // Emite um sinal para notificar a UI após a conclusão do reset
        emit resetFinished();
    });

    // Conecta o fim da execução da thread com um slot que retorna o cursor ao normal
    connect(workerThread, &QThread::finished, this, [=] {
        QString line = ">> Master reset finished.";

        // Verifica se o console estático está inicializado
        if (staticConsole) {
            staticConsole->append(line);  // Adiciona a linha ao console
        } else {
            qDebug() << "Erro: staticConsole não inicializado no final!";
        }

        // Retorna o cursor ao estado normal
        this->setCursor(Qt::ArrowCursor);
        workerThread->deleteLater();  // Deleta a thread após a execução
    });

    // Inicia a execução da thread
    workerThread->start();
}

void MainWindow::onECU3CANBusButtonClicked()
{
    if (this->cursor().shape() == Qt::WaitCursor) {
        QApplication::beep();  // Emite um beep sonoro
        return;
    }
    this->setCursor(Qt::WaitCursor);

    if (!ecuFmController) {
        qDebug() << "Erro: ecuFmController não inicializado!";
                    this->setCursor(Qt::ArrowCursor);  // Retorna o cursor ao normal
        return;
    }

    QThread* workerThread = QThread::create([=] {
        QString line = ">> Toggle ECU#3 CANBus initialized...";
        if (staticConsole) {
            staticConsole->append(line);
        }

        if (ecuFmController) {
            //ESSA É A CERTA
            //ecuFmController->executeTest(JigaTestInterface::MCU_TOG_ECU3BUS_TEST, JigaTestInterface::MCU1_BOARD_ID);
            //PARA TESTES NO MAC
            ecuFmController->executeTest(JigaTestInterface::MCU_TOG_ECU3BUS_TEST, JigaTestInterface::ECU4_BOARD_ID);
        } else {
            qDebug() << "Erro: ecuFmController não inicializado dentro do thread!";
        }

        emit ecu3CANBusFinished();
    });

    connect(workerThread, &QThread::finished, this, [=] {
        QString line = ">> Toggle ECU#3 CANBus finished";
        if (staticConsole) {
            staticConsole->append(line);
        }
        this->setCursor(Qt::ArrowCursor);
        workerThread->deleteLater();
    });

    workerThread->start();
}

void MainWindow::onECU4CANBusButtonClicked()
{
    // Verifica se o cursor atual é um cursor de espera
    if (this->cursor().shape() == Qt::WaitCursor) {
        QApplication::beep();  // Emite um beep sonoro
        return;
    }
    // Define o cursor para o estado de espera
    this->setCursor(Qt::WaitCursor);

    // Verifica se o controlador 'ecuFmController' foi inicializado
    if (!ecuFmController) {
        qDebug() << "Erro: ecuFmController não inicializado!";
                    this->setCursor(Qt::ArrowCursor);  // Retorna o cursor ao normal
        return;
    }

    // Cria uma nova thread para executar o teste de forma assíncrona
    QThread* workerThread = QThread::create([=] {
        // Executa o teste no controlador 'ecuFmController'
        //ESSA É A CERTA
        //ecuFmController->executeTest(JigaTestInterface::MCU_TOG_ECU4BUS_TEST, JigaTestInterface::MCU1_BOARD_ID);
        //PARA TESTES NO MAC
        ecuFmController->executeTest(JigaTestInterface::MCU_TOG_ECU4BUS_TEST, JigaTestInterface::ECU4_BOARD_ID);

        QString line = ">> Toggle ECU#4 CANBus initialized...";
        // Verifica se o console estático está inicializado
        if (staticConsole) {
            staticConsole->append(line);  // Adiciona a linha ao console
        } else {
            qDebug() << "Erro: staticConsole não inicializado!";
        }

        // Emite um sinal para notificar a UI após a conclusão do teste
        emit ecu4CANBusFinished();
    });

    // Conecta o fim da execução da thread com um slot que retorna o cursor ao normal
    connect(workerThread, &QThread::finished, this, [=] {
        QString line = ">> Toggle ECU#4 CANBus finished";
        // Verifica se o console estático está inicializado
        if (staticConsole) {
            staticConsole->append(line);  // Adiciona a linha ao console
        } else {
            qDebug() << "Erro: staticConsole não inicializado no final!";
        }

        // Retorna o cursor ao estado normal
        this->setCursor(Qt::ArrowCursor);
        workerThread->deleteLater();  // Deleta a thread após a execução
    });

    // Inicia a execução da thread
    workerThread->start();
}

void MainWindow::onLoadWebCamButtonClicked()
{
    // Verifica se o cursor atual é um cursor de espera
    if (this->cursor().shape() == Qt::WaitCursor) {
        QApplication::beep();  // Emite um beep sonoro
        return;
    }

    // Cria o widget de vídeo onde a câmera será exibida
    QVideoWidget* videoWidget = new QVideoWidget(this);
    videoWidget->setGeometry(10, 10, 640, 480);  // Ajuste as dimensões conforme necessário
    videoWidget->show();

    // Cria a instância de RCWebcam e a move para um novo thread
    QThread* thread = new QThread;
    RCWebcam* webcam = new RCWebcam(videoWidget);
    webcam->moveToThread(thread);

    connect(thread, &QThread::started, webcam, &RCWebcam::run);
    connect(webcam, &RCWebcam::finished, thread, &QThread::quit);
    connect(webcam, &RCWebcam::finished, webcam, &RCWebcam::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void MainWindow::onCleanConsoleButtonClicked(){
    if (staticConsole) {
        staticConsole->clear();
    }
}

//void MainWindow::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    Q_UNUSED(context);

//    // Formata a mensagem de acordo com o tipo
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

//    // Acesso direto via ui
//    if (staticConsole) {
//        staticConsole->append(formattedMessage);
//    }

//}

void MainWindow::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
        abort(); // Aqui é onde o programa está abortando
    }
}

