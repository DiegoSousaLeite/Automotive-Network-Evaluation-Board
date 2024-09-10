#include "LINNetworkMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
LINNetworkMenu* LINNetworkMenu::instance = nullptr;

// Construtor privado
LINNetworkMenu::LINNetworkMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

LINNetworkMenu* LINNetworkMenu::getInstance() {
    if (instance == nullptr) {
        instance = new LINNetworkMenu();
    }
    return instance;
}

void LINNetworkMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Duração total do teste: 05 segundos (timeout)                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique que a ECU3 e ECU4 estão conectadas                         ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?               r  - Retornar                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void LINNetworkMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                      TESTE DA REDE LIN INICIADO                          ##";
    qDebug() << "##############################################################################";
}

void LINNetworkMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                      TESTE DA REDE LIN FINALIZADO                        ##";
    qDebug() << "##############################################################################";
}

void LINNetworkMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                     RELATORIO DO TESTE DA REDE LIN                       ##";
    qDebug() << "##############################################################################";
}
