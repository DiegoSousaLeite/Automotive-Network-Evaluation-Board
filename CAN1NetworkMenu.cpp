#include "CAN1NetworkMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
CAN1NetworkMenu* CAN1NetworkMenu::instance = nullptr;

// Definição explícita do construtor
CAN1NetworkMenu::CAN1NetworkMenu() {
    // Construtor privado, pode ser vazio ou conter inicializações específicas
}

CAN1NetworkMenu* CAN1NetworkMenu::getInstance() {
    if (instance == nullptr) {
        instance = new CAN1NetworkMenu();
    }
    return instance;
}

void CAN1NetworkMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 0  - CAN1 Network (ECU1-ECU2)        1  - CAN1 Network (ECU1-ECU3)       ##";
    qDebug() << "## 2  - CAN1 Network (ECU1-ECU4)        3  - CAN1 Network (ECU2-ECU3)       ##";
    qDebug() << "## 4  - CAN1 Network (ECU2-ECU4)        5  - CAN1 Network (ECU3-ECU4)       ##";
    qDebug() << "## 7  - CAN1 Network (TODOS)            r  - Retornar                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void CAN1NetworkMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Duração total do teste: 10 segundos (timeout)                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique de que todas as ECUs estejam conectadas                    ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?               r  - Retornar                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void CAN1NetworkMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DA REDE CAN (CANBUS1) INICIADO                    ##";
    qDebug() << "##############################################################################";
}

void CAN1NetworkMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DA REDE CAN (CANBUS1) FINALIZADO                  ##";
    qDebug() << "##############################################################################";
}

void CAN1NetworkMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                RELATÓRIO DO TESTE DA REDE CAN (CANBUS1)                  ##";
    qDebug() << "##############################################################################";
}
