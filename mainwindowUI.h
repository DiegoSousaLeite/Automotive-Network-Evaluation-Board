#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <QIcon>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    // Widget declarations
    QWidget *centralwidget;
    QPushButton *firmwareButton;
    QFrame *line;
    QFrame *line_2;
    QPushButton *virtualButton;
    QPushButton *dashboardButton;
    QPushButton *serialConsoleButton;
    QTextBrowser *textBrowser;
    QComboBox *comboBox;
    QPushButton *firmwareUpdateButton;
    QPushButton *masterResetButton;
    QPushButton *ecu3Button;
    QPushButton *ecu4Button;
    QPushButton *cleanConsoleButton;
    QPushButton *cameraButton;
    QPushButton *loadButton;
    QFrame *line_3;
    QFrame *line_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QStackedWidget *stackedWidget;
    QWidget *pageFirmware;
    QWidget *pageVirtual;
    QWidget *pageDashboard;
    QWidget *pageSerialConsole;


    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1060, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");

        // StackeWidget configuration
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0,50,1081,491));

        pageFirmware = new QWidget();
        pageFirmware->setObjectName("pageFirmware");
        stackedWidget->addWidget(pageFirmware);

        pageVirtual = new QWidget();
        pageVirtual->setObjectName("pageVirtual");
        stackedWidget->addWidget(pageVirtual);

        // Lines configuration
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(0, -5, 3000, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 40, 3000, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        line_3 = new QFrame(pageFirmware);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(0, 60, 3000, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        line_4 = new QFrame(pageFirmware);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(0, 100, 3000, 3));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        // Firmware Button menu configuration
        firmwareButton = new QPushButton(centralwidget);
        firmwareButton->setObjectName("firmwareButton");
        firmwareButton->setGeometry(QRect(10, 10, 110, 32));

        // Virtual Button menu configuration
        virtualButton = new QPushButton(centralwidget);
        virtualButton->setObjectName("virtualButton");
        virtualButton->setGeometry(QRect(130, 10, 110, 32));

        // Dashboard Button menu configuration
        dashboardButton = new QPushButton(centralwidget);
        dashboardButton->setObjectName("dashboardButton");
        dashboardButton->setGeometry(QRect(250, 10, 110, 32));

        // Serial Console Button configuration
        serialConsoleButton = new QPushButton(centralwidget);
        serialConsoleButton->setObjectName("serialConsoleButton");
        serialConsoleButton->setGeometry(QRect(370, 10, 110, 32));

        // TextBrowser configuration
        textBrowser = new QTextBrowser(pageFirmware);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(20, 20, 141, 31));
        textBrowser->setStyleSheet("background-color: transparent;");


        // ComboBox configuration
        comboBox = new QComboBox(pageFirmware);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(180, 20, 611, 32));

        // Firmware Uptade Button configuration
        firmwareUpdateButton = new QPushButton(pageFirmware);
        firmwareUpdateButton->setObjectName("firmwareUpdateButton");
        firmwareUpdateButton->setIcon(QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/update.png"));
        firmwareUpdateButton->setGeometry(QRect(10, 70, 140, 32));
        firmwareUpdateButton->setIconSize(QSize(20,30));
        firmwareUpdateButton->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; }");

        // Master Reset Button configuration
        masterResetButton = new QPushButton(pageFirmware);
        masterResetButton->setObjectName("masterResetButton");
        masterResetButton->setIcon(QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/reset.png"));
        masterResetButton->setGeometry(QRect(160, 70, 140, 32));
        masterResetButton->setIconSize(QSize(20,30));
        masterResetButton->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; }");

        // ECU3 Button configuration
        ecu3Button = new QPushButton(pageFirmware);
        ecu3Button->setObjectName("ecu3Button");
        ecu3Button->setIcon(QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/ecu.png"));
        ecu3Button->setGeometry(QRect(310, 70, 140, 32));
        ecu3Button->setIconSize(QSize(20,30));
        ecu3Button->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; }");

        // ECU4 Button configuration
        ecu4Button = new QPushButton(pageFirmware);
        ecu4Button->setObjectName("ecu4Button");
        ecu4Button->setIcon(QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/ecu.png"));
        ecu4Button->setGeometry(QRect(460, 70, 140, 32));
        ecu4Button->setIconSize(QSize(20,30));
        ecu4Button->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; }");

        // Clean Console Button configuration
        cleanConsoleButton = new QPushButton(pageFirmware);
        cleanConsoleButton->setObjectName("cleanConsoleButton");
        cleanConsoleButton->setIcon(QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/clean.png"));
        cleanConsoleButton->setGeometry(QRect(610, 70, 140, 32));
        cleanConsoleButton->setIconSize(QSize(20,30));
        cleanConsoleButton->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; }");

        // Camera Button configuration
        cameraButton = new QPushButton(pageFirmware);
        cameraButton->setObjectName("cameraButton");
        cameraButton->setIcon(QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/camera.png"));
        cameraButton->setGeometry(QRect(760, 70, 140, 32));
        cameraButton->setIconSize(QSize(20,30));
        cameraButton->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; }");

        // Load Button configuration
        loadButton = new QPushButton(pageFirmware);
        loadButton->setObjectName("loadButton");
        loadButton->setIcon(QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/load.png"));
        loadButton->setGeometry(QRect(910, 70, 140, 32));
        loadButton->setIconSize(QSize(20,30));
        loadButton->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; }");


        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1057, 38));
        MainWindow->setMenuBar(menubar);

        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        firmwareButton->setText(QCoreApplication::translate("MainWindow", "Firmware", nullptr));
        virtualButton->setText(QCoreApplication::translate("MainWindow", "Virtual I/O", nullptr));
        dashboardButton->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        serialConsoleButton->setText(QCoreApplication::translate("MainWindow", "Serial Console", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                       "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
                                                                       "p, li { white-space: pre-wrap; }\n"
                                                                       "hr { height: 1px; border-width: 0; }\n"
                                                                       "li.unchecked::marker { content: \"\\2610\"; }\n"
                                                                       "li.checked::marker { content: \"\\2612\"; }\n"
                                                                       "</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
                                                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ECU Serial Port</p></body></html>", nullptr));
        firmwareUpdateButton->setText(QCoreApplication::translate("MainWindow", "Firmware Uptade", nullptr));
        masterResetButton->setText(QCoreApplication::translate("MainWindow", "  Master Reset", nullptr));
        ecu3Button->setText(QCoreApplication::translate("MainWindow", "ECU#3 - CANBUS1", nullptr));
        ecu4Button->setText(QCoreApplication::translate("MainWindow", "ECU#4 - CANBUS1", nullptr));
        cleanConsoleButton->setText(QCoreApplication::translate("MainWindow", " Clean Console", nullptr));
        cameraButton->setText(QCoreApplication::translate("MainWindow", "  Camera", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "  Load", nullptr));
    } // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui
