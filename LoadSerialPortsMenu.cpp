#include "LoadSerialPortsMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
LoadSerialPortsMenu* LoadSerialPortsMenu::instance = nullptr;

// Construtor privado
LoadSerialPortsMenu::LoadSerialPortsMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

LoadSerialPortsMenu* LoadSerialPortsMenu::getInstance() {
    if (instance == nullptr) {
        instance = new LoadSerialPortsMenu();
    }
    return instance;
}

void LoadSerialPortsMenu::printOptionMenu() {
    MainMenu::getInstance()->printCheckConnectionsMenu();
}

void LoadSerialPortsMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printCheckConnectionsMenu();
}

void LoadSerialPortsMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##          TESTE DE CARREGAMENTO DAS PORTAS SERIAIS INICIADO               ##";
    qDebug() << "##############################################################################";
}

void LoadSerialPortsMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##          TESTE DE CARREGAMENTO DAS PORTAS SERIAIS FINALIZADO             ##";
    qDebug() << "##############################################################################";
}
