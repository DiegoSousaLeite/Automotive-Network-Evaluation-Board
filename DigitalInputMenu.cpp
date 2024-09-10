#include "DigitalInputMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
DigitalInputMenu* DigitalInputMenu::instance = nullptr;

// Construtor privado
DigitalInputMenu::DigitalInputMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

DigitalInputMenu* DigitalInputMenu::getInstance() {
    if (instance == nullptr) {
        instance = new DigitalInputMenu();
    }
    return instance;
}

void DigitalInputMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Entrada digital (ECU1)          2 - Entrada digital (ECU2)          ##";
    qDebug() << "## 3  - Entrada digital (ECU3)          4 - Entrada digital (ECU4)          ##";
    qDebug() << "## 5  - Entrada digital (MCU1)          6 - Entrada digital (TODOS)         ##";
    qDebug() << "## r  - Retornar                                                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void DigitalInputMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Diga Importante! Antes de iniciar:                                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique que o cabo USB tipo B esteja conectado                     ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?               r  - Retornar                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void DigitalInputMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DAS ENTRADAS DIGITAIS INICIADO                    ##";
    qDebug() << "##############################################################################";
}

void DigitalInputMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  TESTE DAS ENTRADAS DIGITAIS FINALIZADO                  ##";
    qDebug() << "##############################################################################";
}

void DigitalInputMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                  RELATÓRIO DO TESTE DAS ENTRADAS DIGITAIS                ##";
    qDebug() << "##############################################################################";
}
