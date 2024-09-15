/********************************************************************************
** Form generated from reading UI file 'aneb.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANEB_H
#define UI_ANEB_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ANEB
{
public:
    QGridLayout *gridLayout;
    QWidget *widgetMenu;
    QVBoxLayout *verticalLayout_5;
    QWidget *widgetTeste;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *changeButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton_14;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_15;
    QStackedWidget *stackedWidgetMainPages;
    QWidget *comunicacaoPage;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayoutComm;
    QHBoxLayout *horizontalCommTest;
    QPushButton *testComm;
    QPushButton *testCAN1;
    QPushButton *testCAN2;
    QPushButton *testInit;
    QPushButton *testLIN;
    QPushButton *testLoop;
    QStackedWidget *stackedWidgetCommTest;
    QWidget *commTest;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalCommOpt;
    QVBoxLayout *verticalLayout_8;
    QPushButton *ecu1;
    QPushButton *ecu3;
    QPushButton *mcu1;
    QVBoxLayout *verticalLayout_9;
    QPushButton *ecu2;
    QPushButton *ecu4;
    QPushButton *todos;
    QTextBrowser *console;
    QWidget *page_4;
    QWidget *page_2;
    QWidget *fullMenuWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayoutLogo2;
    QLabel *logo_label_2;
    QLabel *logo_label_3;
    QVBoxLayout *verticalLayoutMenu;
    QPushButton *homeButton2;
    QPushButton *ioButton2;
    QPushButton *otherButton2;
    QPushButton *ferramentasButton2;
    QPushButton *dashButton2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *exitButton2;
    QWidget *iconOnlyWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayoutLogo;
    QLabel *logo_label_1;
    QVBoxLayout *verticalLayoutIcons;
    QPushButton *commButton;
    QPushButton *ioButton;
    QPushButton *otherButton;
    QPushButton *ferramentasButton;
    QPushButton *dashButton;
    QSpacerItem *verticalSpacer;
    QPushButton *exitButton;

    void setupUi(QWidget *ANEB)
    {
        if (ANEB->objectName().isEmpty())
            ANEB->setObjectName("ANEB");
        ANEB->resize(1351, 551);
        gridLayout = new QGridLayout(ANEB);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widgetMenu = new QWidget(ANEB);
        widgetMenu->setObjectName("widgetMenu");
        verticalLayout_5 = new QVBoxLayout(widgetMenu);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widgetTeste = new QWidget(widgetMenu);
        widgetTeste->setObjectName("widgetTeste");
        widgetTeste->setMinimumSize(QSize(0, 40));
        horizontalLayout_4 = new QHBoxLayout(widgetTeste);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        changeButton = new QPushButton(widgetTeste);
        changeButton->setObjectName("changeButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/menu-4-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        changeButton->setIcon(icon);
        changeButton->setIconSize(QSize(14, 14));
        changeButton->setCheckable(true);
        changeButton->setAutoExclusive(false);

        horizontalLayout_4->addWidget(changeButton);

        horizontalSpacer = new QSpacerItem(82, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEdit = new QLineEdit(widgetTeste);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton_14 = new QPushButton(widgetTeste);
        pushButton_14->setObjectName("pushButton_14");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/search-13-48.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_14->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_14);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(82, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButton_15 = new QPushButton(widgetTeste);
        pushButton_15->setObjectName("pushButton_15");

        horizontalLayout_4->addWidget(pushButton_15);


        verticalLayout_5->addWidget(widgetTeste);

        stackedWidgetMainPages = new QStackedWidget(widgetMenu);
        stackedWidgetMainPages->setObjectName("stackedWidgetMainPages");
        comunicacaoPage = new QWidget();
        comunicacaoPage->setObjectName("comunicacaoPage");
        gridLayout_2 = new QGridLayout(comunicacaoPage);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayoutComm = new QVBoxLayout();
        verticalLayoutComm->setObjectName("verticalLayoutComm");
        horizontalCommTest = new QHBoxLayout();
        horizontalCommTest->setObjectName("horizontalCommTest");
        testComm = new QPushButton(comunicacaoPage);
        testComm->setObjectName("testComm");

        horizontalCommTest->addWidget(testComm);

        testCAN1 = new QPushButton(comunicacaoPage);
        testCAN1->setObjectName("testCAN1");

        horizontalCommTest->addWidget(testCAN1);

        testCAN2 = new QPushButton(comunicacaoPage);
        testCAN2->setObjectName("testCAN2");

        horizontalCommTest->addWidget(testCAN2);

        testInit = new QPushButton(comunicacaoPage);
        testInit->setObjectName("testInit");

        horizontalCommTest->addWidget(testInit);

        testLIN = new QPushButton(comunicacaoPage);
        testLIN->setObjectName("testLIN");

        horizontalCommTest->addWidget(testLIN);

        testLoop = new QPushButton(comunicacaoPage);
        testLoop->setObjectName("testLoop");

        horizontalCommTest->addWidget(testLoop);


        verticalLayoutComm->addLayout(horizontalCommTest);

        stackedWidgetCommTest = new QStackedWidget(comunicacaoPage);
        stackedWidgetCommTest->setObjectName("stackedWidgetCommTest");
        commTest = new QWidget();
        commTest->setObjectName("commTest");
        gridLayout_3 = new QGridLayout(commTest);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalCommOpt = new QHBoxLayout();
        horizontalCommOpt->setSpacing(10);
        horizontalCommOpt->setObjectName("horizontalCommOpt");
        horizontalCommOpt->setContentsMargins(100, 0, 100, 0);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        ecu1 = new QPushButton(commTest);
        ecu1->setObjectName("ecu1");

        verticalLayout_8->addWidget(ecu1);

        ecu3 = new QPushButton(commTest);
        ecu3->setObjectName("ecu3");

        verticalLayout_8->addWidget(ecu3);

        mcu1 = new QPushButton(commTest);
        mcu1->setObjectName("mcu1");

        verticalLayout_8->addWidget(mcu1);


        horizontalCommOpt->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        ecu2 = new QPushButton(commTest);
        ecu2->setObjectName("ecu2");

        verticalLayout_9->addWidget(ecu2);

        ecu4 = new QPushButton(commTest);
        ecu4->setObjectName("ecu4");

        verticalLayout_9->addWidget(ecu4);

        todos = new QPushButton(commTest);
        todos->setObjectName("todos");

        verticalLayout_9->addWidget(todos);


        horizontalCommOpt->addLayout(verticalLayout_9);


        gridLayout_3->addLayout(horizontalCommOpt, 0, 0, 1, 1);

        console = new QTextBrowser(commTest);
        console->setObjectName("console");

        gridLayout_3->addWidget(console, 1, 0, 1, 1);

        stackedWidgetCommTest->addWidget(commTest);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidgetCommTest->addWidget(page_4);

        verticalLayoutComm->addWidget(stackedWidgetCommTest);


        gridLayout_2->addLayout(verticalLayoutComm, 0, 0, 1, 1);

        stackedWidgetMainPages->addWidget(comunicacaoPage);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetMainPages->addWidget(page_2);

        verticalLayout_5->addWidget(stackedWidgetMainPages);


        gridLayout->addWidget(widgetMenu, 2, 3, 2, 1);

        fullMenuWidget = new QWidget(ANEB);
        fullMenuWidget->setObjectName("fullMenuWidget");
        verticalLayout_4 = new QVBoxLayout(fullMenuWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutLogo2 = new QHBoxLayout();
        horizontalLayoutLogo2->setSpacing(0);
        horizontalLayoutLogo2->setObjectName("horizontalLayoutLogo2");
        logo_label_2 = new QLabel(fullMenuWidget);
        logo_label_2->setObjectName("logo_label_2");
        logo_label_2->setMinimumSize(QSize(50, 40));
        logo_label_2->setMaximumSize(QSize(50, 40));
        logo_label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/anebLogo.png")));
        logo_label_2->setScaledContents(true);

        horizontalLayoutLogo2->addWidget(logo_label_2);

        logo_label_3 = new QLabel(fullMenuWidget);
        logo_label_3->setObjectName("logo_label_3");
        QFont font;
        font.setPointSize(15);
        logo_label_3->setFont(font);

        horizontalLayoutLogo2->addWidget(logo_label_3);


        verticalLayout_4->addLayout(horizontalLayoutLogo2);

        verticalLayoutMenu = new QVBoxLayout();
        verticalLayoutMenu->setSpacing(14);
        verticalLayoutMenu->setObjectName("verticalLayoutMenu");
        verticalLayoutMenu->setContentsMargins(-1, 24, -1, -1);
        homeButton2 = new QPushButton(fullMenuWidget);
        homeButton2->setObjectName("homeButton2");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/home-4-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/icons/home-4-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        homeButton2->setIcon(icon2);
        homeButton2->setIconSize(QSize(14, 14));
        homeButton2->setCheckable(true);
        homeButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(homeButton2);

        ioButton2 = new QPushButton(fullMenuWidget);
        ioButton2->setObjectName("ioButton2");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/dashboard-5-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        ioButton2->setIcon(icon3);
        ioButton2->setCheckable(true);
        ioButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(ioButton2);

        otherButton2 = new QPushButton(fullMenuWidget);
        otherButton2->setObjectName("otherButton2");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/borcelle.png"), QSize(), QIcon::Normal, QIcon::On);
        otherButton2->setIcon(icon4);
        otherButton2->setIconSize(QSize(14, 14));
        otherButton2->setCheckable(true);
        otherButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(otherButton2);

        ferramentasButton2 = new QPushButton(fullMenuWidget);
        ferramentasButton2->setObjectName("ferramentasButton2");
        ferramentasButton2->setIcon(icon4);
        ferramentasButton2->setIconSize(QSize(14, 14));
        ferramentasButton2->setCheckable(true);
        ferramentasButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(ferramentasButton2);

        dashButton2 = new QPushButton(fullMenuWidget);
        dashButton2->setObjectName("dashButton2");
        dashButton2->setIcon(icon4);
        dashButton2->setIconSize(QSize(14, 14));
        dashButton2->setCheckable(true);
        dashButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(dashButton2);


        verticalLayout_4->addLayout(verticalLayoutMenu);

        verticalSpacer_2 = new QSpacerItem(20, 290, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        exitButton2 = new QPushButton(fullMenuWidget);
        exitButton2->setObjectName("exitButton2");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/close-window-64.ico"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton2->setIcon(icon5);
        exitButton2->setIconSize(QSize(14, 14));

        verticalLayout_4->addWidget(exitButton2);


        gridLayout->addWidget(fullMenuWidget, 2, 2, 2, 1);

        iconOnlyWidget = new QWidget(ANEB);
        iconOnlyWidget->setObjectName("iconOnlyWidget");
        verticalLayout_3 = new QVBoxLayout(iconOnlyWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutLogo = new QHBoxLayout();
        horizontalLayoutLogo->setSpacing(0);
        horizontalLayoutLogo->setObjectName("horizontalLayoutLogo");
        horizontalLayoutLogo->setContentsMargins(0, 0, 0, 0);
        logo_label_1 = new QLabel(iconOnlyWidget);
        logo_label_1->setObjectName("logo_label_1");
        logo_label_1->setMinimumSize(QSize(50, 50));
        logo_label_1->setMaximumSize(QSize(45, 50));
        logo_label_1->setPixmap(QPixmap(QString::fromUtf8(":/icons/anebLogo.png")));
        logo_label_1->setScaledContents(true);

        horizontalLayoutLogo->addWidget(logo_label_1);


        verticalLayout_3->addLayout(horizontalLayoutLogo);

        verticalLayoutIcons = new QVBoxLayout();
        verticalLayoutIcons->setSpacing(10);
        verticalLayoutIcons->setObjectName("verticalLayoutIcons");
        commButton = new QPushButton(iconOnlyWidget);
        commButton->setObjectName("commButton");
        commButton->setIcon(icon2);
        commButton->setIconSize(QSize(20, 20));
        commButton->setCheckable(true);
        commButton->setAutoRepeat(false);
        commButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(commButton);

        ioButton = new QPushButton(iconOnlyWidget);
        ioButton->setObjectName("ioButton");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/dashboard-5-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/icons/dashboard-5-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        icon6.addFile(QString::fromUtf8(":/icons/dashboard-5-48.ico"), QSize(), QIcon::Disabled, QIcon::On);
        ioButton->setIcon(icon6);
        ioButton->setIconSize(QSize(20, 20));
        ioButton->setCheckable(true);
        ioButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(ioButton);

        otherButton = new QPushButton(iconOnlyWidget);
        otherButton->setObjectName("otherButton");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/botao.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/new/prefix1/refresh.png"), QSize(), QIcon::Normal, QIcon::On);
        icon7.addFile(QString::fromUtf8(":/icons/borcelle.png"), QSize(), QIcon::Disabled, QIcon::On);
        otherButton->setIcon(icon7);
        otherButton->setIconSize(QSize(20, 20));
        otherButton->setCheckable(true);
        otherButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(otherButton);

        ferramentasButton = new QPushButton(iconOnlyWidget);
        ferramentasButton->setObjectName("ferramentasButton");
        ferramentasButton->setIcon(icon7);
        ferramentasButton->setIconSize(QSize(20, 20));
        ferramentasButton->setCheckable(true);
        ferramentasButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(ferramentasButton);

        dashButton = new QPushButton(iconOnlyWidget);
        dashButton->setObjectName("dashButton");
        dashButton->setIcon(icon7);
        dashButton->setIconSize(QSize(20, 20));
        dashButton->setCheckable(true);
        dashButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(dashButton);


        verticalLayout_3->addLayout(verticalLayoutIcons);

        verticalSpacer = new QSpacerItem(20, 286, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        exitButton = new QPushButton(iconOnlyWidget);
        exitButton->setObjectName("exitButton");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/new/prefix1/botao.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon8.addFile(QString::fromUtf8(":/new/prefix1/botao.png"), QSize(), QIcon::Normal, QIcon::On);
        icon8.addFile(QString::fromUtf8(":/icons/close-window-64.ico"), QSize(), QIcon::Disabled, QIcon::On);
        exitButton->setIcon(icon8);
        exitButton->setIconSize(QSize(20, 20));

        verticalLayout_3->addWidget(exitButton);


        gridLayout->addWidget(iconOnlyWidget, 2, 0, 1, 1);


        retranslateUi(ANEB);
        QObject::connect(changeButton, &QPushButton::toggled, iconOnlyWidget, &QWidget::setVisible);
        QObject::connect(changeButton, &QPushButton::toggled, fullMenuWidget, &QWidget::setHidden);
        QObject::connect(commButton, &QPushButton::toggled, homeButton2, &QPushButton::setChecked);
        QObject::connect(ioButton, &QPushButton::toggled, ioButton2, &QPushButton::setChecked);
        QObject::connect(otherButton, &QPushButton::toggled, otherButton2, &QPushButton::setChecked);
        QObject::connect(ferramentasButton, &QPushButton::toggled, ferramentasButton2, &QPushButton::setChecked);
        QObject::connect(dashButton, &QPushButton::toggled, dashButton2, &QPushButton::setChecked);
        QObject::connect(homeButton2, &QPushButton::toggled, commButton, &QPushButton::setChecked);
        QObject::connect(ioButton2, &QPushButton::toggled, ioButton, &QPushButton::setChecked);
        QObject::connect(otherButton2, &QPushButton::toggled, otherButton, &QPushButton::setChecked);
        QObject::connect(ferramentasButton2, &QPushButton::toggled, ferramentasButton, &QPushButton::setChecked);
        QObject::connect(dashButton2, &QPushButton::toggled, dashButton, &QPushButton::setChecked);
        QObject::connect(exitButton, &QPushButton::clicked, ANEB, qOverload<>(&QWidget::close));
        QObject::connect(exitButton2, &QPushButton::clicked, ANEB, qOverload<>(&QWidget::close));

        stackedWidgetMainPages->setCurrentIndex(0);
        stackedWidgetCommTest->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ANEB);
    } // setupUi

    void retranslateUi(QWidget *ANEB)
    {
        ANEB->setWindowTitle(QCoreApplication::translate("ANEB", "Form", nullptr));
        changeButton->setText(QString());
        pushButton_14->setText(QString());
        pushButton_15->setText(QCoreApplication::translate("ANEB", "PushButton", nullptr));
        testComm->setText(QCoreApplication::translate("ANEB", "Teste de Comunica\303\247\303\243o", nullptr));
        testCAN1->setText(QCoreApplication::translate("ANEB", "Teste de Rede CAN (CAN1)", nullptr));
        testCAN2->setText(QCoreApplication::translate("ANEB", "Teste de Rede CAN (CAN2)", nullptr));
        testInit->setText(QCoreApplication::translate("ANEB", "Teste de Inicializa\303\247\303\243o(CAN)", nullptr));
        testLIN->setText(QCoreApplication::translate("ANEB", "Teste da rede LIN", nullptr));
        testLoop->setText(QCoreApplication::translate("ANEB", "Teste de LoopBack (CAN)", nullptr));
        ecu1->setText(QCoreApplication::translate("ANEB", "ECU1", nullptr));
        ecu3->setText(QCoreApplication::translate("ANEB", "ECU3", nullptr));
        mcu1->setText(QCoreApplication::translate("ANEB", "MCU1", nullptr));
        ecu2->setText(QCoreApplication::translate("ANEB", "ECU2", nullptr));
        ecu4->setText(QCoreApplication::translate("ANEB", "ECU4", nullptr));
        todos->setText(QCoreApplication::translate("ANEB", "TODOS", nullptr));
        logo_label_2->setText(QString());
        logo_label_3->setText(QCoreApplication::translate("ANEB", "Siedebar", nullptr));
        homeButton2->setText(QCoreApplication::translate("ANEB", "Comunica\303\247\303\243o", nullptr));
        ioButton2->setText(QCoreApplication::translate("ANEB", "DashBoard", nullptr));
        otherButton2->setText(QCoreApplication::translate("ANEB", "Ex3", nullptr));
        ferramentasButton2->setText(QCoreApplication::translate("ANEB", "Ex4", nullptr));
        dashButton2->setText(QCoreApplication::translate("ANEB", "Ex5", nullptr));
        exitButton2->setText(QCoreApplication::translate("ANEB", "Exit", nullptr));
        logo_label_1->setText(QString());
        commButton->setText(QString());
        ioButton->setText(QString());
        otherButton->setText(QString());
        ferramentasButton->setText(QString());
        dashButton->setText(QString());
        exitButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ANEB: public Ui_ANEB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANEB_H
