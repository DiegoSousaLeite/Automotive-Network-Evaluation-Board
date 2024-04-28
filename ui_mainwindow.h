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
#include <QLabel>
#include "mainwindow.h"

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

    QTextBrowser *console;

    QPushButton *createButton(QWidget *parent, const QString &objectName, const QIcon &icon, const QRect &geometry, const QSize &iconSize, const QString &styleSheet)
    {
        QPushButton *button = new QPushButton(parent);
        button->setObjectName(objectName);
        button->setIcon(icon);
        button->setGeometry(geometry);
        button->setIconSize(iconSize);
        button->setStyleSheet(styleSheet);
        return button;
    }

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("ANEB 2.0");

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

        console = new QTextBrowser(pageFirmware);
        console->setObjectName("console");
        console->setGeometry(QRect(10,110,1051,450));

        // Firmware Uptade Button configuration
        firmwareUpdateButton = createButton(pageFirmware, "firmwareUpdateButton", QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/update.png"),
                                            QRect(10, 70, 141, 32),QSize(20,30),"QPushButton { text-align: left; padding-left: 5px; }");

        // Master Reset Button configuration
        masterResetButton = createButton(pageFirmware,"masterResetButton",QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/reset.png"),
                                         QRect(161, 70, 141, 32),QSize(20,30),"QPushButton { text-align: left; padding-left: 5px; }");

        // ECU3 Button configuration
        ecu3Button = createButton(pageFirmware,"ecu3Button",QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/ecu.png"),
                                  QRect(312, 70, 151, 32),QSize(20,30),"QPushButton { text-align: left; padding-left: 5px; }");

        // ECU4 Button configuration
        ecu4Button = createButton(pageFirmware,"ecu4Button",QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/ecu.png"),
                                  QRect(473, 70, 151, 32),QSize(20,30),"QPushButton { text-align: left; padding-left: 5px; }");

        // Clean Console Button configuration
        cleanConsoleButton = createButton(pageFirmware,"cleanConsoleButton",QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/clean.png"),
                                          QRect(634, 70, 141, 32),QSize(20,30),"QPushButton { text-align: left; padding-left: 5px; }");

        // Camera Button configuration
        cameraButton = createButton(pageFirmware,"cameraButton",QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/camera.png"),
                                    QRect(785, 70, 133, 32),QSize(20,30),"QPushButton { text-align: left; padding-left: 5px; }");

        // Load Button configuration
        loadButton = createButton(pageFirmware,"laodButton",QIcon("/Users/sousadiego/Documents/ws-Qt/ANEB_2/icons/load.png"),
                                    QRect(928, 70, 133, 32),QSize(20,30),"QPushButton { text-align: left; padding-left: 5px; }");

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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ANEB 2.0", nullptr));
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
