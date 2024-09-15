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
    QSpacerItem *horizontalSpacer_2;
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
    QPushButton *clearButton;
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
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QTextBrowser *console_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *startButton;
    QPushButton *clearButton_2;
    QWidget *dashPage;
    QWidget *page_2;
    QWidget *page;
    QWidget *page_3;
    QWidget *fullMenuWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayoutLogo2;
    QLabel *logo_label_2;
    QLabel *logo_label_3;
    QVBoxLayout *verticalLayoutMenu;
    QPushButton *commButton2;
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
        ANEB->resize(1453, 551);
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
        icon.addFile(QString::fromUtf8(":/icons/menuW.png"), QSize(), QIcon::Normal, QIcon::Off);
        changeButton->setIcon(icon);
        changeButton->setIconSize(QSize(20, 20));
        changeButton->setCheckable(true);
        changeButton->setAutoExclusive(false);

        horizontalLayout_4->addWidget(changeButton);

        horizontalSpacer = new QSpacerItem(82, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalSpacer_2 = new QSpacerItem(82, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


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
        testComm->setMinimumSize(QSize(0, 0));
        testComm->setCheckable(true);
        testComm->setAutoExclusive(true);

        horizontalCommTest->addWidget(testComm);

        testCAN1 = new QPushButton(comunicacaoPage);
        testCAN1->setObjectName("testCAN1");
        testCAN1->setCheckable(true);
        testCAN1->setAutoExclusive(true);

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
        clearButton = new QPushButton(commTest);
        clearButton->setObjectName("clearButton");

        gridLayout_3->addWidget(clearButton, 3, 1, 1, 1);

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

        gridLayout_3->addWidget(console, 1, 0, 3, 1);

        stackedWidgetCommTest->addWidget(commTest);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        gridLayout_4 = new QGridLayout(page_4);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        console_2 = new QTextBrowser(page_4);
        console_2->setObjectName("console_2");

        horizontalLayout->addWidget(console_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        startButton = new QPushButton(page_4);
        startButton->setObjectName("startButton");

        verticalLayout->addWidget(startButton);

        clearButton_2 = new QPushButton(page_4);
        clearButton_2->setObjectName("clearButton_2");

        verticalLayout->addWidget(clearButton_2);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        stackedWidgetCommTest->addWidget(page_4);

        verticalLayoutComm->addWidget(stackedWidgetCommTest);


        gridLayout_2->addLayout(verticalLayoutComm, 0, 0, 1, 1);

        stackedWidgetMainPages->addWidget(comunicacaoPage);
        dashPage = new QWidget();
        dashPage->setObjectName("dashPage");
        stackedWidgetMainPages->addWidget(dashPage);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidgetMainPages->addWidget(page_2);
        page = new QWidget();
        page->setObjectName("page");
        stackedWidgetMainPages->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidgetMainPages->addWidget(page_3);

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
        logo_label_2->setMinimumSize(QSize(50, 38));
        logo_label_2->setMaximumSize(QSize(50, 40));
        logo_label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/ANEBW.png")));
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
        commButton2 = new QPushButton(fullMenuWidget);
        commButton2->setObjectName("commButton2");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/antenna-3-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/icons/antenna-3-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        commButton2->setIcon(icon1);
        commButton2->setIconSize(QSize(14, 14));
        commButton2->setCheckable(true);
        commButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(commButton2);

        ioButton2 = new QPushButton(fullMenuWidget);
        ioButton2->setObjectName("ioButton2");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/plug-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/icons/plug-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        ioButton2->setIcon(icon2);
        ioButton2->setIconSize(QSize(14, 14));
        ioButton2->setCheckable(true);
        ioButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(ioButton2);

        otherButton2 = new QPushButton(fullMenuWidget);
        otherButton2->setObjectName("otherButton2");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/test-tube-2-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/icons/test-tube-2-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        otherButton2->setIcon(icon3);
        otherButton2->setIconSize(QSize(14, 14));
        otherButton2->setCheckable(true);
        otherButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(otherButton2);

        ferramentasButton2 = new QPushButton(fullMenuWidget);
        ferramentasButton2->setObjectName("ferramentasButton2");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/wrench-2-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/icons/wrench-2-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        ferramentasButton2->setIcon(icon4);
        ferramentasButton2->setIconSize(QSize(14, 14));
        ferramentasButton2->setCheckable(true);
        ferramentasButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(ferramentasButton2);

        dashButton2 = new QPushButton(fullMenuWidget);
        dashButton2->setObjectName("dashButton2");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/dashboard-5-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/icons/dashboard-5-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        dashButton2->setIcon(icon5);
        dashButton2->setIconSize(QSize(14, 14));
        dashButton2->setCheckable(true);
        dashButton2->setAutoExclusive(true);

        verticalLayoutMenu->addWidget(dashButton2);


        verticalLayout_4->addLayout(verticalLayoutMenu);

        verticalSpacer_2 = new QSpacerItem(20, 290, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        exitButton2 = new QPushButton(fullMenuWidget);
        exitButton2->setObjectName("exitButton2");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/close-window-64.ico"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton2->setIcon(icon6);
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
        logo_label_1->setMinimumSize(QSize(66, 70));
        logo_label_1->setMaximumSize(QSize(70, 70));
        logo_label_1->setPixmap(QPixmap(QString::fromUtf8(":/icons/ANEBW.png")));
        logo_label_1->setScaledContents(true);
        logo_label_1->setWordWrap(false);
        logo_label_1->setMargin(0);
        logo_label_1->setIndent(-1);

        horizontalLayoutLogo->addWidget(logo_label_1);


        verticalLayout_3->addLayout(horizontalLayoutLogo);

        verticalLayoutIcons = new QVBoxLayout();
        verticalLayoutIcons->setSpacing(10);
        verticalLayoutIcons->setObjectName("verticalLayoutIcons");
        commButton = new QPushButton(iconOnlyWidget);
        commButton->setObjectName("commButton");
        commButton->setIcon(icon1);
        commButton->setIconSize(QSize(20, 20));
        commButton->setCheckable(true);
        commButton->setAutoRepeat(false);
        commButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(commButton);

        ioButton = new QPushButton(iconOnlyWidget);
        ioButton->setObjectName("ioButton");
        ioButton->setIcon(icon2);
        ioButton->setIconSize(QSize(20, 20));
        ioButton->setCheckable(true);
        ioButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(ioButton);

        otherButton = new QPushButton(iconOnlyWidget);
        otherButton->setObjectName("otherButton");
        otherButton->setIcon(icon3);
        otherButton->setIconSize(QSize(20, 20));
        otherButton->setCheckable(true);
        otherButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(otherButton);

        ferramentasButton = new QPushButton(iconOnlyWidget);
        ferramentasButton->setObjectName("ferramentasButton");
        ferramentasButton->setIcon(icon4);
        ferramentasButton->setIconSize(QSize(20, 20));
        ferramentasButton->setCheckable(true);
        ferramentasButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(ferramentasButton);

        dashButton = new QPushButton(iconOnlyWidget);
        dashButton->setObjectName("dashButton");
        dashButton->setIcon(icon5);
        dashButton->setIconSize(QSize(20, 20));
        dashButton->setCheckable(true);
        dashButton->setAutoExclusive(true);

        verticalLayoutIcons->addWidget(dashButton);


        verticalLayout_3->addLayout(verticalLayoutIcons);

        verticalSpacer = new QSpacerItem(20, 286, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        exitButton = new QPushButton(iconOnlyWidget);
        exitButton->setObjectName("exitButton");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/botao.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/new/prefix1/botao.png"), QSize(), QIcon::Normal, QIcon::On);
        icon7.addFile(QString::fromUtf8(":/icons/close-window-64.ico"), QSize(), QIcon::Disabled, QIcon::On);
        exitButton->setIcon(icon7);
        exitButton->setIconSize(QSize(20, 20));

        verticalLayout_3->addWidget(exitButton);


        gridLayout->addWidget(iconOnlyWidget, 2, 0, 1, 1);


        retranslateUi(ANEB);
        QObject::connect(changeButton, &QPushButton::toggled, iconOnlyWidget, &QWidget::setVisible);
        QObject::connect(changeButton, &QPushButton::toggled, fullMenuWidget, &QWidget::setHidden);
        QObject::connect(commButton, &QPushButton::toggled, commButton2, &QPushButton::setChecked);
        QObject::connect(ioButton, &QPushButton::toggled, ioButton2, &QPushButton::setChecked);
        QObject::connect(otherButton, &QPushButton::toggled, otherButton2, &QPushButton::setChecked);
        QObject::connect(ferramentasButton, &QPushButton::toggled, ferramentasButton2, &QPushButton::setChecked);
        QObject::connect(dashButton, &QPushButton::toggled, dashButton2, &QPushButton::setChecked);
        QObject::connect(commButton2, &QPushButton::toggled, commButton, &QPushButton::setChecked);
        QObject::connect(ioButton2, &QPushButton::toggled, ioButton, &QPushButton::setChecked);
        QObject::connect(otherButton2, &QPushButton::toggled, otherButton, &QPushButton::setChecked);
        QObject::connect(ferramentasButton2, &QPushButton::toggled, ferramentasButton, &QPushButton::setChecked);
        QObject::connect(dashButton2, &QPushButton::toggled, dashButton, &QPushButton::setChecked);
        QObject::connect(exitButton, &QPushButton::clicked, ANEB, qOverload<>(&QWidget::close));
        QObject::connect(exitButton2, &QPushButton::clicked, ANEB, qOverload<>(&QWidget::close));

        stackedWidgetMainPages->setCurrentIndex(0);
        stackedWidgetCommTest->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ANEB);
    } // setupUi

    void retranslateUi(QWidget *ANEB)
    {
        ANEB->setWindowTitle(QCoreApplication::translate("ANEB", "Form", nullptr));
        changeButton->setText(QString());
        testComm->setText(QCoreApplication::translate("ANEB", "Teste de Comunica\303\247\303\243o", nullptr));
        testCAN1->setText(QCoreApplication::translate("ANEB", "Teste de Rede CAN (CAN1)", nullptr));
        testCAN2->setText(QCoreApplication::translate("ANEB", "Teste de Rede CAN (CAN2)", nullptr));
        testInit->setText(QCoreApplication::translate("ANEB", "Teste de Inicializa\303\247\303\243o(CAN)", nullptr));
        testLIN->setText(QCoreApplication::translate("ANEB", "Teste da rede LIN", nullptr));
        testLoop->setText(QCoreApplication::translate("ANEB", "Teste de LoopBack (CAN)", nullptr));
        clearButton->setText(QCoreApplication::translate("ANEB", "Clear", nullptr));
        ecu1->setText(QCoreApplication::translate("ANEB", "ECU1", nullptr));
        ecu3->setText(QCoreApplication::translate("ANEB", "ECU3", nullptr));
        mcu1->setText(QCoreApplication::translate("ANEB", "MCU1", nullptr));
        ecu2->setText(QCoreApplication::translate("ANEB", "ECU2", nullptr));
        ecu4->setText(QCoreApplication::translate("ANEB", "ECU4", nullptr));
        todos->setText(QCoreApplication::translate("ANEB", "TODOS", nullptr));
        startButton->setText(QCoreApplication::translate("ANEB", "Start", nullptr));
        clearButton_2->setText(QCoreApplication::translate("ANEB", "Clear", nullptr));
        logo_label_2->setText(QString());
        logo_label_3->setText(QCoreApplication::translate("ANEB", "Siedebar", nullptr));
        commButton2->setText(QCoreApplication::translate("ANEB", "Comunica\303\247\303\243o", nullptr));
        ioButton2->setText(QCoreApplication::translate("ANEB", "I/O", nullptr));
        otherButton2->setText(QCoreApplication::translate("ANEB", "Outros", nullptr));
        ferramentasButton2->setText(QCoreApplication::translate("ANEB", "Ferramentas", nullptr));
        dashButton2->setText(QCoreApplication::translate("ANEB", "DashBoard", nullptr));
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
