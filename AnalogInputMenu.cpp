#include "AnalogInputMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
AnalogInputMenu* AnalogInputMenu::instance = nullptr;

// Construtor privado
AnalogInputMenu::AnalogInputMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

AnalogInputMenu* AnalogInputMenu::getInstance() {
    if (instance == nullptr) {
        instance = new AnalogInputMenu();
    }
    return instance;
}

void AnalogInputMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Entrada analógica (ECU1)        2 - Entrada analógica (ECU2)        ##";
    qDebug() << "## 3  - Entrada analógica (ECU3)        4 - Entrada analógica (ECU4)        ##";
    qDebug() << "## 6  - Entrada analógica (TODOS)       r - Retornar                        ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void AnalogInputMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Duração total do teste: 20 segundos (timeout)                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Gire todos os potenciômetros durante o timeout                        ##";
    qDebug() << "## b) Gire completamente o potenciômetro (em ambos os sentidos)             ##";
    qDebug() << "## c) LEDs ECU# acende/apaga quando se alcança o final do curso             ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?               r  - Retornar                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void AnalogInputMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                TESTE DAS ENTRADAS ANALÓGICAS INICIADO                    ##";
    qDebug() << "##############################################################################";
}

void AnalogInputMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                TESTE DAS ENTRADAS ANALÓGICAS FINALIZADO                  ##";
    qDebug() << "##############################################################################";
}

void AnalogInputMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##               RELATÓRIO DO TESTE DAS ENTRADAS ANALÓGICAS                 ##";
    qDebug() << "##############################################################################";
}
