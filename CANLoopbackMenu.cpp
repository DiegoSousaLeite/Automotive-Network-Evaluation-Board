#include "CANLoopbackMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
CANLoopbackMenu* CANLoopbackMenu::instance = nullptr;

// Construtor privado
CANLoopbackMenu::CANLoopbackMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

CANLoopbackMenu* CANLoopbackMenu::getInstance() {
    if (instance == nullptr) {
        instance = new CANLoopbackMenu();
    }
    return instance;
}

void CANLoopbackMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Loopback CAN (ECU1)             2 - Loopback CAN (ECU2)             ##";
    qDebug() << "## 3  - Loopback CAN (ECU3)             4 - Loopback CAN (ECU4)             ##";
    qDebug() << "## 6  - Loopback CAN (TODOS)            r - Retornar                        ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void CANLoopbackMenu::printWarningMessageMenu() {
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

void CANLoopbackMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##       TESTE DE LOOPBACK DOS CONTROLADORES CAN INICIADO                   ##";
    qDebug() << "##############################################################################";
}

void CANLoopbackMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##       TESTE DE LOOPBACK DOS CONTROLADORES CAN FINALIZADO                 ##";
    qDebug() << "##############################################################################";
}

void CANLoopbackMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##       RELATÓRIO DO TESTE DE LOOPBACK DOS CONTROLADORES CAN               ##";
    qDebug() << "##############################################################################";
}
