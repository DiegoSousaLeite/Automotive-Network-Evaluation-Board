#include "MCUInterfaceMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
MCUInterfaceMenu* MCUInterfaceMenu::instance = nullptr;

// Construtor privado
MCUInterfaceMenu::MCUInterfaceMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

MCUInterfaceMenu* MCUInterfaceMenu::getInstance() {
    if (instance == nullptr) {
        instance = new MCUInterfaceMenu();
    }
    return instance;
}

void MCUInterfaceMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Identifica porta                2 - Selecionar rede CAN1            ##";
    qDebug() << "## 3  - Selecionar rede CAN2            4 - Ativar reset externo            ##";
    qDebug() << "## 5  - Desativar reset externo         6 - Ativar reset externo (timeout)  ##";
    qDebug() << "## r  - Retornar                                                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void MCUInterfaceMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printCheckConnectionsMenu();
}

void MCUInterfaceMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DE INTERFACE DA MCU INICIADO                      ##";
    qDebug() << "##############################################################################";
}

void MCUInterfaceMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DE INTERFACE DA MCU FINALIZADO                    ##";
    qDebug() << "##############################################################################";
}
