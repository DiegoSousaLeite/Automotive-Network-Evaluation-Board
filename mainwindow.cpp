#include "mainwindow.h"
#include <QStackedWidget>
#include "virtual_io.h"
#include <QFileDialog>
#include <QTextBrowser>
#include <QMessageBox>
#include <QList>
#include <QSerialPortInfo>


// Constructor for MainWindow class
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    setFixedSize(1071, 600);
    ui->setupUi(this); // Setup the UI elements based on the design from Qt Designer
    staticConsole = ui->console;  // Inicializa o console estático
    setupButtonStyles(); // Function call to centralize the style configuration and page switching setup
    qInstallMessageHandler(myMessageOutput);  // Instala o manipulador de log personalizado
    updateComboBoxCommPortList(); // Atualiza a lista de portas seriais na inicialização

    // Create the Virtual_IO widget, set its parent to ui->pageVirtual for proper hierarchy
    virtualIOWidget = new Virtual_IO(ui->pageVirtual);
    virtualIOWidget->setGeometry(QRect(0,-40,1081,491)); // Adjust the size to fit the parent widget
    virtualIOWidget->hide(); // Hide the widget initially until the respective button is clicked

    // Connect the 'virtualButton' click to the function that shows the Virtual_IO page
    connect(ui->virtualButton, &QPushButton::clicked, this, &MainWindow::showVirtualIO);

    connect(ui->firmwareUpdateButton, &QPushButton::clicked, this, &MainWindow::onFirmwareUpdateButtonClicked);
    connect(ui->cleanConsoleButton, &QPushButton::clicked,this,&MainWindow::onCleanConsoleButtonClicked);
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::updateComboBoxCommPortList);


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

void MainWindow::initializeDevice()
{
    SystemDefinition sDefinition;  // Supondo que esta classe esteja definida
    sDefinition.printSystemProperties();  // Supondo método de impressão

    PersistenceController* psController = PersistenceController::getInstance();

    bool deviceFound = psController->loadUsbProgrammer();
    if (!deviceFound) {
        qDebug() << "USBASC not found!";
    } else {
        qDebug() << "USBASC Found";
        /*
        qDebug() << "Serial Number =" << psController->getUsbDeviceSerialNumber();
        qDebug() << "Product ID =" << psController->getUsbDeviceProductString();
        qDebug() << "Manufacturer =" << psController->getUsbDeviceManufacturerString();
        */
    }
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

