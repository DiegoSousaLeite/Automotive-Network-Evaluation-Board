#include "mainwindow.h"
#include <QStackedWidget>
#include "virtual_io.h"

// Constructor for MainWindow class
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); // Setup the UI elements based on the design from Qt Designer
    setupButtonStyles(); // Function call to centralize the style configuration and page switching setup

    // Create the Virtual_IO widget, set its parent to ui->pageVirtual for proper hierarchy
    virtualIOWidget = new Virtual_IO(ui->pageVirtual);
    virtualIOWidget->setGeometry(QRect(0,-40,1081,491)); // Adjust the size to fit the parent widget
    virtualIOWidget->hide(); // Hide the widget initially until the respective button is clicked

    // Connect the 'virtualButton' click to the function that shows the Virtual_IO page
    connect(ui->virtualButton, &QPushButton::clicked, this, &MainWindow::showVirtualIO);

    // Apply an active style to the firmware button, as it's the main/start page
    QString activeButtonStyle = "QPushButton { "
                                "background-color: rgba(0, 0, 255, 128); "
                                "border-radius: 15px; "
                                "}";
    ui->firmwareButton->setStyleSheet(activeButtonStyle);
    ui->stackedWidget->setCurrentWidget(ui->pageFirmware); // Set the initial visible page to firmware

}

// Destructor for MainWindow class
MainWindow::~MainWindow() {
    delete ui; // Clean up the Ui::MainWindow object when the MainWindow object is destroyed
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
