#include "McuUploadMenu.h"
#include <QDebug>

// Inicialização do ponteiro estático
McuUploadMenu* McuUploadMenu::instance = nullptr;

// Construtor privado
McuUploadMenu::McuUploadMenu() {
    // Construtor pode ser vazio ou conter inicializações específicas
}

McuUploadMenu* McuUploadMenu::getInstance() {
    if (instance == nullptr) {
        instance = new McuUploadMenu();
    }
    return instance;
}

void McuUploadMenu::printOptionMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Diga Importante! Antes de iniciar:                                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique que o cabo USB tipo B esteja conectado                     ##";
    qDebug() << "## b) Certifique que o programador esteja conectado corretamente            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione um programador para iniciar a gravação:                        ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  -  Arduino as ISP                2  - USBasp                          ##";
    qDebug() << "## r  -  Retornar                                                           ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void McuUploadMenu::printWarningMessageMenu() {
    MainMenu::getInstance()->printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Diga Importante! Antes de iniciar:                                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique que o cabo USB tipo B esteja conectado                     ##";
    qDebug() << "## b) Certifique que o programador esteja conectado corretamente            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione um programador para iniciar a gravação:                        ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  -  Arduino as ISP                2  - USBasp                          ##";
    qDebug() << "## r  -  Retornar                                                           ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void McuUploadMenu::printStartedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##              ATUALIZAÇÃO DE FIRMWARE DA MCU INICIADA                     ##";
    qDebug() << "##############################################################################";
}

void McuUploadMenu::printFinishedTestMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##              ATUALIZAÇÃO DE FIRMWARE DA MCU FINALIZADA                   ##";
    qDebug() << "##############################################################################";
}
