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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ANEB
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *changeButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton_14;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_15;
    QStackedWidget *stackedWidget;
    QWidget *comunicacaoPage;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_12;
    QStackedWidget *stackedWidget_2;
    QWidget *commTest;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pushButton_13;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pushButton_20;
    QPushButton *pushButton_19;
    QPushButton *pushButton_18;
    QWidget *page_4;
    QWidget *page_2;
    QWidget *fullMenuWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *logo_label_2;
    QLabel *logo_label_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *homeButton2;
    QPushButton *dashButton2;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QSpacerItem *verticalSpacer_2;
    QPushButton *exitButton2;
    QWidget *iconOnlyWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *logo_label_1;
    QVBoxLayout *verticalLayout;
    QPushButton *homeButton;
    QPushButton *dashButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
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
        widget_3 = new QWidget(ANEB);
        widget_3->setObjectName("widget_3");
        verticalLayout_5 = new QVBoxLayout(widget_3);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(widget_3);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 40));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        changeButton = new QPushButton(widget);
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
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton_14 = new QPushButton(widget);
        pushButton_14->setObjectName("pushButton_14");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/search-13-48.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_14->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_14);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(82, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButton_15 = new QPushButton(widget);
        pushButton_15->setObjectName("pushButton_15");

        horizontalLayout_4->addWidget(pushButton_15);


        verticalLayout_5->addWidget(widget);

        stackedWidget = new QStackedWidget(widget_3);
        stackedWidget->setObjectName("stackedWidget");
        comunicacaoPage = new QWidget();
        comunicacaoPage->setObjectName("comunicacaoPage");
        gridLayout_2 = new QGridLayout(comunicacaoPage);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pushButton = new QPushButton(comunicacaoPage);
        pushButton->setObjectName("pushButton");

        horizontalLayout_5->addWidget(pushButton);

        pushButton_6 = new QPushButton(comunicacaoPage);
        pushButton_6->setObjectName("pushButton_6");

        horizontalLayout_5->addWidget(pushButton_6);

        pushButton_8 = new QPushButton(comunicacaoPage);
        pushButton_8->setObjectName("pushButton_8");

        horizontalLayout_5->addWidget(pushButton_8);

        pushButton_2 = new QPushButton(comunicacaoPage);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_5->addWidget(pushButton_2);

        pushButton_7 = new QPushButton(comunicacaoPage);
        pushButton_7->setObjectName("pushButton_7");

        horizontalLayout_5->addWidget(pushButton_7);

        pushButton_12 = new QPushButton(comunicacaoPage);
        pushButton_12->setObjectName("pushButton_12");

        horizontalLayout_5->addWidget(pushButton_12);


        verticalLayout_6->addLayout(horizontalLayout_5);

        stackedWidget_2 = new QStackedWidget(comunicacaoPage);
        stackedWidget_2->setObjectName("stackedWidget_2");
        commTest = new QWidget();
        commTest->setObjectName("commTest");
        gridLayout_3 = new QGridLayout(commTest);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(100, 0, 100, 300);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        pushButton_13 = new QPushButton(commTest);
        pushButton_13->setObjectName("pushButton_13");

        verticalLayout_8->addWidget(pushButton_13);

        pushButton_16 = new QPushButton(commTest);
        pushButton_16->setObjectName("pushButton_16");

        verticalLayout_8->addWidget(pushButton_16);

        pushButton_17 = new QPushButton(commTest);
        pushButton_17->setObjectName("pushButton_17");

        verticalLayout_8->addWidget(pushButton_17);


        horizontalLayout_6->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        pushButton_20 = new QPushButton(commTest);
        pushButton_20->setObjectName("pushButton_20");

        verticalLayout_9->addWidget(pushButton_20);

        pushButton_19 = new QPushButton(commTest);
        pushButton_19->setObjectName("pushButton_19");

        verticalLayout_9->addWidget(pushButton_19);

        pushButton_18 = new QPushButton(commTest);
        pushButton_18->setObjectName("pushButton_18");

        verticalLayout_9->addWidget(pushButton_18);


        horizontalLayout_6->addLayout(verticalLayout_9);


        gridLayout_3->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        stackedWidget_2->addWidget(commTest);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidget_2->addWidget(page_4);

        verticalLayout_6->addWidget(stackedWidget_2);


        gridLayout_2->addLayout(verticalLayout_6, 0, 0, 1, 1);

        stackedWidget->addWidget(comunicacaoPage);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        verticalLayout_5->addWidget(stackedWidget);


        gridLayout->addWidget(widget_3, 2, 3, 2, 1);

        fullMenuWidget = new QWidget(ANEB);
        fullMenuWidget->setObjectName("fullMenuWidget");
        verticalLayout_4 = new QVBoxLayout(fullMenuWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        logo_label_2 = new QLabel(fullMenuWidget);
        logo_label_2->setObjectName("logo_label_2");
        logo_label_2->setMinimumSize(QSize(50, 40));
        logo_label_2->setMaximumSize(QSize(50, 40));
        logo_label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/anebLogo.png")));
        logo_label_2->setScaledContents(true);

        horizontalLayout_2->addWidget(logo_label_2);

        logo_label_3 = new QLabel(fullMenuWidget);
        logo_label_3->setObjectName("logo_label_3");
        QFont font;
        font.setPointSize(15);
        logo_label_3->setFont(font);

        horizontalLayout_2->addWidget(logo_label_3);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(14);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 24, -1, -1);
        homeButton2 = new QPushButton(fullMenuWidget);
        homeButton2->setObjectName("homeButton2");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/home-4-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/icons/home-4-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        homeButton2->setIcon(icon2);
        homeButton2->setIconSize(QSize(14, 14));
        homeButton2->setCheckable(true);
        homeButton2->setAutoExclusive(true);

        verticalLayout_2->addWidget(homeButton2);

        dashButton2 = new QPushButton(fullMenuWidget);
        dashButton2->setObjectName("dashButton2");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/dashboard-5-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        dashButton2->setIcon(icon3);
        dashButton2->setCheckable(true);
        dashButton2->setAutoExclusive(true);

        verticalLayout_2->addWidget(dashButton2);

        pushButton_9 = new QPushButton(fullMenuWidget);
        pushButton_9->setObjectName("pushButton_9");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/borcelle.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_9->setIcon(icon4);
        pushButton_9->setIconSize(QSize(14, 14));
        pushButton_9->setCheckable(true);
        pushButton_9->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(fullMenuWidget);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setIcon(icon4);
        pushButton_10->setIconSize(QSize(14, 14));
        pushButton_10->setCheckable(true);
        pushButton_10->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton_10);

        pushButton_11 = new QPushButton(fullMenuWidget);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setIcon(icon4);
        pushButton_11->setIconSize(QSize(14, 14));
        pushButton_11->setCheckable(true);
        pushButton_11->setAutoExclusive(true);

        verticalLayout_2->addWidget(pushButton_11);


        verticalLayout_4->addLayout(verticalLayout_2);

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
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        logo_label_1 = new QLabel(iconOnlyWidget);
        logo_label_1->setObjectName("logo_label_1");
        logo_label_1->setMinimumSize(QSize(50, 50));
        logo_label_1->setMaximumSize(QSize(45, 50));
        logo_label_1->setPixmap(QPixmap(QString::fromUtf8(":/icons/anebLogo.png")));
        logo_label_1->setScaledContents(true);

        horizontalLayout_3->addWidget(logo_label_1);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        homeButton = new QPushButton(iconOnlyWidget);
        homeButton->setObjectName("homeButton");
        homeButton->setIcon(icon2);
        homeButton->setIconSize(QSize(20, 20));
        homeButton->setCheckable(true);
        homeButton->setAutoRepeat(false);
        homeButton->setAutoExclusive(true);

        verticalLayout->addWidget(homeButton);

        dashButton = new QPushButton(iconOnlyWidget);
        dashButton->setObjectName("dashButton");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/dashboard-5-32.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/icons/dashboard-5-48.ico"), QSize(), QIcon::Normal, QIcon::On);
        icon6.addFile(QString::fromUtf8(":/icons/dashboard-5-48.ico"), QSize(), QIcon::Disabled, QIcon::On);
        dashButton->setIcon(icon6);
        dashButton->setIconSize(QSize(20, 20));
        dashButton->setCheckable(true);
        dashButton->setAutoExclusive(true);

        verticalLayout->addWidget(dashButton);

        pushButton_3 = new QPushButton(iconOnlyWidget);
        pushButton_3->setObjectName("pushButton_3");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/botao.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/new/prefix1/refresh.png"), QSize(), QIcon::Normal, QIcon::On);
        icon7.addFile(QString::fromUtf8(":/icons/borcelle.png"), QSize(), QIcon::Disabled, QIcon::On);
        pushButton_3->setIcon(icon7);
        pushButton_3->setIconSize(QSize(20, 20));
        pushButton_3->setCheckable(true);
        pushButton_3->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(iconOnlyWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setIcon(icon7);
        pushButton_4->setIconSize(QSize(20, 20));
        pushButton_4->setCheckable(true);
        pushButton_4->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(iconOnlyWidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setIcon(icon7);
        pushButton_5->setIconSize(QSize(20, 20));
        pushButton_5->setCheckable(true);
        pushButton_5->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_5);


        verticalLayout_3->addLayout(verticalLayout);

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
        QObject::connect(homeButton, &QPushButton::toggled, homeButton2, &QPushButton::setChecked);
        QObject::connect(dashButton, &QPushButton::toggled, dashButton2, &QPushButton::setChecked);
        QObject::connect(pushButton_3, &QPushButton::toggled, pushButton_9, &QPushButton::setChecked);
        QObject::connect(pushButton_4, &QPushButton::toggled, pushButton_10, &QPushButton::setChecked);
        QObject::connect(pushButton_5, &QPushButton::toggled, pushButton_11, &QPushButton::setChecked);
        QObject::connect(homeButton2, &QPushButton::toggled, homeButton, &QPushButton::setChecked);
        QObject::connect(dashButton2, &QPushButton::toggled, dashButton, &QPushButton::setChecked);
        QObject::connect(pushButton_9, &QPushButton::toggled, pushButton_3, &QPushButton::setChecked);
        QObject::connect(pushButton_10, &QPushButton::toggled, pushButton_4, &QPushButton::setChecked);
        QObject::connect(pushButton_11, &QPushButton::toggled, pushButton_5, &QPushButton::setChecked);
        QObject::connect(exitButton, &QPushButton::clicked, ANEB, qOverload<>(&QWidget::close));
        QObject::connect(exitButton2, &QPushButton::clicked, ANEB, qOverload<>(&QWidget::close));

        stackedWidget->setCurrentIndex(0);
        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ANEB);
    } // setupUi

    void retranslateUi(QWidget *ANEB)
    {
        ANEB->setWindowTitle(QCoreApplication::translate("ANEB", "Form", nullptr));
        changeButton->setText(QString());
        pushButton_14->setText(QString());
        pushButton_15->setText(QCoreApplication::translate("ANEB", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("ANEB", "Teste de Comunica\303\247\303\243o", nullptr));
        pushButton_6->setText(QCoreApplication::translate("ANEB", "Teste de Rede CAN (CAN1)", nullptr));
        pushButton_8->setText(QCoreApplication::translate("ANEB", "Teste de Rede CAN (CAN2)", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ANEB", "Teste de Inicializa\303\247\303\243o(CAN)", nullptr));
        pushButton_7->setText(QCoreApplication::translate("ANEB", "Teste da rede LIN", nullptr));
        pushButton_12->setText(QCoreApplication::translate("ANEB", "Teste de LoopBack (CAN)", nullptr));
        pushButton_13->setText(QCoreApplication::translate("ANEB", "ECU1", nullptr));
        pushButton_16->setText(QCoreApplication::translate("ANEB", "ECU3", nullptr));
        pushButton_17->setText(QCoreApplication::translate("ANEB", "MCU1", nullptr));
        pushButton_20->setText(QCoreApplication::translate("ANEB", "ECU2", nullptr));
        pushButton_19->setText(QCoreApplication::translate("ANEB", "ECU4", nullptr));
        pushButton_18->setText(QCoreApplication::translate("ANEB", "TODOS", nullptr));
        logo_label_2->setText(QString());
        logo_label_3->setText(QCoreApplication::translate("ANEB", "Siedebar", nullptr));
        homeButton2->setText(QCoreApplication::translate("ANEB", "Comunica\303\247\303\243o", nullptr));
        dashButton2->setText(QCoreApplication::translate("ANEB", "DashBoard", nullptr));
        pushButton_9->setText(QCoreApplication::translate("ANEB", "Ex3", nullptr));
        pushButton_10->setText(QCoreApplication::translate("ANEB", "Ex4", nullptr));
        pushButton_11->setText(QCoreApplication::translate("ANEB", "Ex5", nullptr));
        exitButton2->setText(QCoreApplication::translate("ANEB", "Exit", nullptr));
        logo_label_1->setText(QString());
        homeButton->setText(QString());
        dashButton->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        exitButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ANEB: public Ui_ANEB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANEB_H
