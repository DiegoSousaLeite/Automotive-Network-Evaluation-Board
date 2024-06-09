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
    qDebug() << "Initializing McuBusinessController...";
    McuBusinessController mcuBController;
    mcuBController.setPersistenceController(psController);

    bool progLoaded = mcuBController.loadProgrammer(JigaTestConstants::SERIAL_PROG_ID);
    if (progLoaded) {
        qDebug() << "Programmer is loaded!";
        mcuBController.uploadFirmware(JigaTestConstants::SERIAL_PROG_ID);
    } else {
        qDebug() << "Programmer is not loaded!";
    }

    QThread::sleep(3); // Simulating delay

    // Inicializando EcuBusinessController
    qDebug() << "Initializing EcuBusinessController...";
    EcuBusinessController ecuBController;
    ecuBController.setPersistenceController(psController);

    int portFounds = psController->findSerialCommPorts();
    qDebug() << "Number of ports =" << portFounds;

    for (int i = 0; i < portFounds; ++i) {
        int index = psController->getCommPortFound(i);
        qDebug() << "[" << i << "] : (" << psController->getPortDescription(index) << ") : ("
                 << psController->getDescriptivePortName(index) << ")";
    }

    QThread::sleep(3); // Simulating delay

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
    if (this->cursor().shape() == Qt::WaitCursor) {
        QApplication::beep();
        return;
    }
    this->setCursor(Qt::WaitCursor);
    qDebug() << "Chegou aqui";

    if (!ecuFmController) {
        qDebug() << "Erro: ecuFmController não inicializado!";
                    this->setCursor(Qt::ArrowCursor);
        return;
    }

    QThread* workerThread = QThread::create([=] {
        qDebug() << "Chegou aqui2";
        QString line = ">> Master reset initialized...";
        staticConsole->append(line);
        qDebug() << "Chegou aqui3";

        // Assumindo que ecuFmController é um membro da classe MainWindow
        ecuFmController->executeTest(JigaTestConstants::MCU_RST_ATT_TEST, JigaTestConstants::MCU1_BOARD_ID);

        // Emitimos um sinal para notificar a UI após a conclusão do reset
        emit resetFinished();
    });

    // Conectamos o fim do trabalho no thread com o slot que retorna o cursor ao normal
    connect(workerThread, &QThread::finished, this, [=] {
        QString line = ">> Master reset finished.";
        staticConsole->append(line);
        this->setCursor(Qt::ArrowCursor);
        workerThread->deleteLater(); // Limpamos o thread após a execução
    });

    workerThread->start(); // Adicione esta linha para iniciar o thread
}

void MainWindow::onCleanConsoleButtonClicked(){
    if (staticConsole) {
        staticConsole->clear();
    }
}

void MainWindow::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
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

    // Acesso direto via ui
    if (staticConsole) {
        staticConsole->append(formattedMessage);
    }

}

//void MainWindow::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
//    switch (type) {
//    case QtDebugMsg:
//        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
//        break;
//    case QtInfoMsg:
//        fprintf(stderr, "Info: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
//        break;
//    case QtWarningMsg:
//        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
//        break;
//    case QtCriticalMsg:
//        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
//        break;
//    case QtFatalMsg:
//        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
//        abort(); // Aqui é onde o programa está abortando
//    }
//}

