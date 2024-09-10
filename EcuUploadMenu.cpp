#include "EcuUploadMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
EcuUploadMenu* EcuUploadMenu::instance= nullptr;

// Construtor privado
EcuUploadMenu::EcuUploadMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

EcuUploadMenu* EcuUploadMenu::getInstance() {
    if (instance == nullptr) {
        instance = new EcuUploadMenu();
    }
    return instance;
}

void EcuUploadMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Gravar firmware(ECU1)           2 - Gravar firmware(ECU2)           ##";
    qDebug() << "## 3  - Gravar firmware(ECU3)           4 - Gravar firmware(ECU4)           ##";
    qDebug() << "## 5  - Gravar firmware(MCU1)           6 - Gravar firmware(ECUs)           ##";
    qDebug() << "## r  - Retornar                                                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void EcuUploadMenu::printEcuProcessorMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - ATmega328P (Old Bootloader)     2 - ATMega328P                      ##";
    qDebug() << "## r  - Retornar                                                            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void EcuUploadMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Diga Importante! Antes de iniciar:                                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique que o cabo USB tipo B esteja conectado                     ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar gravacao?               r  - Retornar                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void EcuUploadMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                ATUALIZAÇÃO DE FIRMWARE INICIADA                          ##";
    qDebug() << "##############################################################################";
}

void EcuUploadMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                ATUALIZAÇÃO DE FIRMWARE FINALIZADA                        ##";
    qDebug() << "##############################################################################";
}

void EcuUploadMenu::printReportTestMenu() {
    // Função vazia, conforme o código Java original
}
