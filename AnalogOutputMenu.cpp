#include "AnalogOutputMenu.h"

AnalogOutputMenu* AnalogOutputMenu::instance = nullptr;

// Definição explícita do construtor
AnalogOutputMenu::AnalogOutputMenu() {
    // Construtor privado, vazio ou com inicializações específicas, se necessário
}

AnalogOutputMenu* AnalogOutputMenu::getInstance() {
    if (instance == nullptr) {
        instance = new AnalogOutputMenu();
    }
    return instance;
}

void AnalogOutputMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Duração total do teste: 05 segundos (timeout)                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique de que as ECUs 1 e 2 estejam conectadas                    ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?               r  - Retornar                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void AnalogOutputMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                TESTE DAS SAÍDAS ANALÓGICAS INICIADO                      ##";
    qDebug() << "##############################################################################";
}

void AnalogOutputMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                TESTE DAS SAÍDAS ANALÓGICAS FINALIZADO                    ##";
    qDebug() << "##############################################################################";
}

void AnalogOutputMenu::printReportTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                RELATÓRIO DO TESTE DAS SAÍDAS ANALÓGICAS                  ##";
    qDebug() << "##############################################################################";
}
