#include "ReportTestMenus.h"
#include <QDebug>

// Inicialização do ponteiro estático
ReportTestMenus* ReportTestMenus::instance = nullptr;

// Construtor privado
ReportTestMenus::ReportTestMenus() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

ReportTestMenus* ReportTestMenus::getInstance() {
    if (instance == nullptr) {
        instance = new ReportTestMenus();
    }
    return instance;
}

void ReportTestMenus::printReportMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Relatório comunicação           2 - Relatório entrada digital       ##";
    qDebug() << "## 3  - Relatório entrada analógica     4 - Relatório saída analógica       ##";
    qDebug() << "## 5  - Relatório inicialização (CAN)   6 - Relatório loopback (CAN)        ##";
    qDebug() << "## 7  - Relatório rede CAN (CAN1)       8 - Relatório rede CAN (CAN2)       ##";
    qDebug() << "## 9  - Relatório rede LIN              f - Relatório (TODOS)               ##";
    qDebug() << "## r  - Retornar                                                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void ReportTestMenus::printWarningMessageMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "## Diga Importante! Antes de iniciar:                                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique de que tenha executado os testes                           ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?            r  - Retornar                                   ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void ReportTestMenus::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                      RELATÓRIO DE TESTES - INÍCIO                        ##";
    qDebug() << "##############################################################################";
}

void ReportTestMenus::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                      RELATÓRIO DE TESTES - FIM                           ##";
        qDebug() << "##############################################################################";
}
