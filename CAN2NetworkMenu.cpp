#include "CAN2NetworkMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
CAN2NetworkMenu* CAN2NetworkMenu::instance = nullptr;

// Construtor privado
CAN2NetworkMenu::CAN2NetworkMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

CAN2NetworkMenu* CAN2NetworkMenu::getInstance() {
    if (instance == nullptr) {
        instance = new CAN2NetworkMenu();
    }
    return instance;
}

void CAN2NetworkMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - CAN2 Network (ECU2-ECU3)        2  - CAN2 Network (ECU2-ECU4)       ##";
    qDebug() << "## 3  - CAN2 Network (ECU3-ECU4)        6  - CAN2 Network (TODOS)           ##";
    qDebug() << "## r  - Retornar                                                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void CAN2NetworkMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Duração total do teste: 10 segundos (timeout)                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique que o cabo USB tipo B esteja conectado                     ##";
    qDebug() << "## b) Certifique que o cabo conversor USB-TTL PL2303HX esteja conectado     ##";
    qDebug() << "## c) Certifique de que as ECU2, ECU3 e ECU4 estejam conectadas             ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?               r  - Retornar                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void CAN2NetworkMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DA REDE CAN (CANBUS2) INICIADO                    ##";
    qDebug() << "##############################################################################";
}

void CAN2NetworkMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DA REDE CAN (CANBUS2) FINALIZADO                  ##";
    qDebug() << "##############################################################################";
}

void CAN2NetworkMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                RELATÓRIO DO TESTE DA REDE CAN (CANBUS2)                  ##";
    qDebug() << "##############################################################################";
}
