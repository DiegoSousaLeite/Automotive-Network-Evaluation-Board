#include "CANInitMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
CANInitMenu* CANInitMenu::instance = nullptr;

// Construtor privado
CANInitMenu::CANInitMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

CANInitMenu* CANInitMenu::getInstance() {
    if (instance == nullptr) {
        instance = new CANInitMenu();
    }
    return instance;
}

void CANInitMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Inicializar CAN(ECU1)           2 - Inicializar CAN (ECU2)          ##";
    qDebug() << "## 3  - Inicializar CAN(ECU3)           4 - Inicializar CAN (ECU4)          ##";
    qDebug() << "## 6  - Inicializar CAN(TODOS)          r - Retornar                        ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void CANInitMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Duração total do teste: 05 segundos (timeout)                            ##";
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

void CANInitMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##       TESTE DE INICIALIZAÇÃO DOS CONTROLADORES CAN INICIADO              ##";
    qDebug() << "##############################################################################";
}

void CANInitMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##       TESTE DE INICIALIZAÇÃO DOS CONTROLADORES CAN FINALIZADO            ##";
    qDebug() << "##############################################################################";
}

void CANInitMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##       RELATÓRIO DO TESTE DE INICIALIZAÇÃO DOS CONTROLADORES CAN          ##";
    qDebug() << "##############################################################################";
}
