/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *firmwareButton;
    QFrame *line;
    QFrame *line_2;
    QPushButton *virtualButton;
    QPushButton *dashboardButton;
    QPushButton *serialConsoleButton;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QFrame *line_3;
    QComboBox *comboBox;
    QPushButton *firmwareUpdateButton;
    QPushButton *cleanConsoleButton;
    QPushButton *ecu3Button;
    QTextBrowser *textBrowser;
    QPushButton *loadButton;
    QPushButton *cameraButton;
    QPushButton *ecu4Button;
    QPushButton *masterResetButton;
    QFrame *line_4;
    QWidget *page_4;
    QWidget *page_5;
    QWidget *page_3;
    QTableWidget *tableWidget;
    QTextBrowser *textBrowser_3;
    QPushButton *pushButton;
    QFrame *line_7;
    QLineEdit *lineEdit_3;
    QFrame *line_5;
    QFrame *line_6;
    QLineEdit *lineEdit;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_3;
    QSlider *horizontalSlider_3;
    QPushButton *pushButton_6;
    QSlider *horizontalSlider_2;
    QFrame *line_8;
    QPushButton *pushButton_14;
    QTextBrowser *textBrowser_2;
    QLineEdit *lineEdit_4;
    QTextBrowser *textBrowser_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_2;
    QSlider *horizontalSlider_4;
    QFrame *line_9;
    QFrame *line_10;
    QSlider *horizontalSlider;
    QPushButton *pushButton_15;
    QTextBrowser *textBrowser_5;
    QPushButton *pushButton_12;
    QLineEdit *lineEdit_2;
    QFrame *line_11;
    QFrame *line_12;
    QPushButton *pushButton_9;
    QPushButton *pushButton_13;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1082, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        firmwareButton = new QPushButton(centralwidget);
        firmwareButton->setObjectName("firmwareButton");
        firmwareButton->setGeometry(QRect(0, 10, 90, 30));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 40, 1081, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, -5, 1081, 21));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        virtualButton = new QPushButton(centralwidget);
        virtualButton->setObjectName("virtualButton");
        virtualButton->setGeometry(QRect(110, 10, 90, 30));
        dashboardButton = new QPushButton(centralwidget);
        dashboardButton->setObjectName("dashboardButton");
        dashboardButton->setGeometry(QRect(220, 10, 90, 30));
        serialConsoleButton = new QPushButton(centralwidget);
        serialConsoleButton->setObjectName("serialConsoleButton");
        serialConsoleButton->setGeometry(QRect(330, 10, 111, 30));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 50, 1081, 491));
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        line_3 = new QFrame(page_1);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(0, 50, 1181, 16));
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        comboBox = new QComboBox(page_1);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(180, 10, 611, 32));
        firmwareUpdateButton = new QPushButton(page_1);
        firmwareUpdateButton->setObjectName("firmwareUpdateButton");
        firmwareUpdateButton->setGeometry(QRect(10, 60, 140, 32));
        cleanConsoleButton = new QPushButton(page_1);
        cleanConsoleButton->setObjectName("cleanConsoleButton");
        cleanConsoleButton->setGeometry(QRect(610, 60, 140, 32));
        ecu3Button = new QPushButton(page_1);
        ecu3Button->setObjectName("ecu3Button");
        ecu3Button->setGeometry(QRect(310, 60, 140, 32));
        textBrowser = new QTextBrowser(page_1);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(20, 10, 141, 31));
        QFont font;
        font.setKerning(true);
        textBrowser->setFont(font);
        loadButton = new QPushButton(page_1);
        loadButton->setObjectName("loadButton");
        loadButton->setGeometry(QRect(910, 60, 140, 32));
        cameraButton = new QPushButton(page_1);
        cameraButton->setObjectName("cameraButton");
        cameraButton->setGeometry(QRect(760, 60, 140, 32));
        ecu4Button = new QPushButton(page_1);
        ecu4Button->setObjectName("ecu4Button");
        ecu4Button->setGeometry(QRect(460, 60, 140, 32));
        masterResetButton = new QPushButton(page_1);
        masterResetButton->setObjectName("masterResetButton");
        masterResetButton->setGeometry(QRect(160, 60, 140, 32));
        line_4 = new QFrame(page_1);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(0, 100, 1181, 3));
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        stackedWidget->addWidget(page_1);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        stackedWidget->addWidget(page_5);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        tableWidget = new QTableWidget(page_3);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 4, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 5, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 6, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 7, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setCheckState(Qt::Unchecked);
        tableWidget->setItem(0, 8, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        __qtablewidgetitem25->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 5, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 6, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 7, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setCheckState(Qt::Unchecked);
        tableWidget->setItem(1, 8, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        __qtablewidgetitem31->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        __qtablewidgetitem32->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 1, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        __qtablewidgetitem33->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 2, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        __qtablewidgetitem34->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 3, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        __qtablewidgetitem35->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 4, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        __qtablewidgetitem36->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 5, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        __qtablewidgetitem37->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 6, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        __qtablewidgetitem38->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 7, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        __qtablewidgetitem39->setCheckState(Qt::Unchecked);
        tableWidget->setItem(2, 8, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        __qtablewidgetitem40->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 0, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        __qtablewidgetitem41->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 1, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        __qtablewidgetitem42->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 2, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        __qtablewidgetitem43->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 3, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        __qtablewidgetitem44->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 4, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        __qtablewidgetitem45->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 5, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        __qtablewidgetitem46->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 6, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        __qtablewidgetitem47->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 7, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        __qtablewidgetitem48->setCheckState(Qt::Unchecked);
        tableWidget->setItem(3, 8, __qtablewidgetitem48);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(590, 50, 451, 192));
        tableWidget->setSortingEnabled(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        textBrowser_3 = new QTextBrowser(page_3);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(600, 250, 181, 21));
        pushButton = new QPushButton(page_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(870, 280, 100, 21));
        line_7 = new QFrame(page_3);
        line_7->setObjectName("line_7");
        line_7->setGeometry(QRect(575, 20, 3, 380));
        line_7->setFrameShape(QFrame::Shape::VLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);
        lineEdit_3 = new QLineEdit(page_3);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(600, 340, 260, 21));
        line_5 = new QFrame(page_3);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(10, 400, 540, 3));
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);
        line_6 = new QFrame(page_3);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(10, 20, 540, 3));
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);
        lineEdit = new QLineEdit(page_3);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(600, 280, 260, 21));
        pushButton_7 = new QPushButton(page_3);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(90, 70, 50, 32));
        pushButton_8 = new QPushButton(page_3);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(210, 70, 50, 32));
        pushButton_3 = new QPushButton(page_3);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(870, 340, 100, 21));
        horizontalSlider_3 = new QSlider(page_3);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(50, 310, 200, 25));
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        pushButton_6 = new QPushButton(page_3);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(30, 70, 50, 32));
        horizontalSlider_2 = new QSlider(page_3);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(50, 270, 200, 25));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        line_8 = new QFrame(page_3);
        line_8->setObjectName("line_8");
        line_8->setGeometry(QRect(550, 20, 3, 380));
        line_8->setFrameShape(QFrame::Shape::VLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton_14 = new QPushButton(page_3);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(360, 280, 171, 32));
        textBrowser_2 = new QTextBrowser(page_3);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(10, 0, 121, 21));
        lineEdit_4 = new QLineEdit(page_3);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(600, 370, 260, 21));
        textBrowser_4 = new QTextBrowser(page_3);
        textBrowser_4->setObjectName("textBrowser_4");
        textBrowser_4->setGeometry(QRect(580, 20, 181, 21));
        pushButton_5 = new QPushButton(page_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(980, 280, 71, 111));
        pushButton_4 = new QPushButton(page_3);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(870, 370, 100, 21));
        pushButton_10 = new QPushButton(page_3);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(260, 230, 51, 32));
        pushButton_11 = new QPushButton(page_3);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(260, 310, 51, 32));
        pushButton_2 = new QPushButton(page_3);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(870, 310, 100, 21));
        horizontalSlider_4 = new QSlider(page_3);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setGeometry(QRect(50, 350, 200, 25));
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        line_9 = new QFrame(page_3);
        line_9->setObjectName("line_9");
        line_9->setGeometry(QRect(10, 20, 3, 380));
        line_9->setFrameShape(QFrame::Shape::VLine);
        line_9->setFrameShadow(QFrame::Shadow::Sunken);
        line_10 = new QFrame(page_3);
        line_10->setObjectName("line_10");
        line_10->setGeometry(QRect(1060, 20, 3, 380));
        line_10->setFrameShape(QFrame::Shape::VLine);
        line_10->setFrameShadow(QFrame::Shadow::Sunken);
        horizontalSlider = new QSlider(page_3);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(50, 230, 200, 25));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_15 = new QPushButton(page_3);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(360, 320, 171, 32));
        textBrowser_5 = new QTextBrowser(page_3);
        textBrowser_5->setObjectName("textBrowser_5");
        textBrowser_5->setGeometry(QRect(580, 0, 181, 21));
        pushButton_12 = new QPushButton(page_3);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(260, 270, 51, 32));
        lineEdit_2 = new QLineEdit(page_3);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(600, 310, 260, 21));
        line_11 = new QFrame(page_3);
        line_11->setObjectName("line_11");
        line_11->setGeometry(QRect(575, 400, 485, 3));
        line_11->setFrameShape(QFrame::Shape::HLine);
        line_11->setFrameShadow(QFrame::Shadow::Sunken);
        line_12 = new QFrame(page_3);
        line_12->setObjectName("line_12");
        line_12->setGeometry(QRect(575, 20, 485, 3));
        line_12->setFrameShape(QFrame::Shape::HLine);
        line_12->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton_9 = new QPushButton(page_3);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(150, 70, 50, 32));
        pushButton_13 = new QPushButton(page_3);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(260, 350, 51, 32));
        stackedWidget->addWidget(page_3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1082, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        firmwareButton->setText(QCoreApplication::translate("MainWindow", "Firmware", nullptr));
        virtualButton->setText(QCoreApplication::translate("MainWindow", "Virtual I/O", nullptr));
        dashboardButton->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        serialConsoleButton->setText(QCoreApplication::translate("MainWindow", "Serial Console", nullptr));
        firmwareUpdateButton->setText(QCoreApplication::translate("MainWindow", "Firmware Uptade", nullptr));
        cleanConsoleButton->setText(QCoreApplication::translate("MainWindow", "Clean Console", nullptr));
        ecu3Button->setText(QCoreApplication::translate("MainWindow", "ECU#3 - CANBUS1", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ECU Serial Port</p></body></html>", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        cameraButton->setText(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        ecu4Button->setText(QCoreApplication::translate("MainWindow", "ECU#4 - CANBUS1", nullptr));
        masterResetButton->setText(QCoreApplication::translate("MainWindow", "Master Reset", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "N\302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "DIN#1", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "DIN#2", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "DIN#3", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "DIN#4", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "AIN#1", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "AIN#2", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "AIN#3", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "AIN#4", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "ECU#1", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "ECU#2", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "ECU#3", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "ECU#4", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        textBrowser_3->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ECU# Send Data:</p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "ECU#1 Send", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "DIN#2", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "DIN#4", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "ECU#3 Send", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "DIN#1", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "ECUs Connection", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Virtual Input:</p></body></html>", nullptr));
        textBrowser_4->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ECU# Pin Mapping:</p></body></html>", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Send All", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "ECU#4 Send", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "AIN#1", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "AIN#3", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "ECU#2 Send", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Virtual Input (Default Test)", nullptr));
        textBrowser_5->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Virtual I/O Configuration:</p></body></html>", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "AIN#2", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "DIN#3", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "AIN#4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
