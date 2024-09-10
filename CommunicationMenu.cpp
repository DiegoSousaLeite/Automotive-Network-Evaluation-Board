#include "CommunicationMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
CommunicationMenu* CommunicationMenu::instance = nullptr;

// Construtor privado
CommunicationMenu::CommunicationMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

CommunicationMenu* CommunicationMenu::getInstance() {
    if (instance == nullptr) {
        instance = new CommunicationMenu();
    }
    return instance;
}

void CommunicationMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Comunicação ECU1                2 - Comunicação ECU2                ##";
    qDebug() << "## 3  - Comunicação ECU3                4 - Comunicação ECU4                ##";
    qDebug() << "## 5  - Comunicação MCU1                6 - Comunicação (TODOS)             ##";
    qDebug() << "## r  - Retornar                                                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void CommunicationMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printCheckConnectionsMenu();
}

void CommunicationMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                      TESTE DE COMUNICAÇÃO INICIADO                       ##";
    qDebug() << "##############################################################################";
}

void CommunicationMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                      TESTE DE COMUNICAÇÃO FINALIZADO                     ##";
    qDebug() << "##############################################################################";
}

void CommunicationMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                     RELATÓRIO DO TESTE DE COMUNICAÇÃO                    ##";
    qDebug() << "##############################################################################";
}
