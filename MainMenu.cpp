#include "MainMenu.h"

// Inicialização do ponteiro de instância Singleton
MainMenu* MainMenu::instance = nullptr;

MainMenu::MainMenu() {
    // Construtor privado
}

MainMenu* MainMenu::getInstance() {
    if (instance == nullptr) {
        instance = new MainMenu();
    }
    return instance;
}

void MainMenu::printHeaderMenu() {
    qDebug() << "##############################################################################";
    qDebug() << "##                                                                          ##";
    qDebug() << "##                  ANEV v1.0.0 - APLICAÇÃO PARA TESTE v1.2                 ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
}

void MainMenu::printMainMenu() {
    printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Teste de comunicacao            2 - Teste das entradas digitais     ##";
    qDebug() << "## 3  - Teste das entradas analógicas   4 - Teste das saidas analogicas     ##";
    qDebug() << "## 5  - Teste de inicializacao (CAN)    6 - Teste de loopback (CAN)         ##";
    qDebug() << "## 7  - Teste da rede CAN (CAN1)        8 - Teste da rede CAN (CAN2)        ##";
    qDebug() << "## 9  - Teste da rede LIN               0 - Teste de interface (MCU)        ##";
    qDebug() << "## a  - Execução automática de testes   e - Emitir relatório                ##";
    qDebug() << "## g  - Gravação de firmware            s - Carregar portas seriais         ##";
    qDebug() << "## x  - Encerrar programa                                                   ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void MainMenu::printCheckConnectionsMenu() {
    printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Diga Importante! Antes de iniciar:                                       ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique que o cabo USB tipo B esteja conectado                     ##";
    qDebug() << "## b) Certifique que o cabo conversor USB-TTL PL2303HX esteja conectado     ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## Selecione uma das opções:                                                ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar?            r  - Retornar                                   ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}

void MainMenu::printWarningMessageMenu() {
    printHeaderMenu();
    qDebug() << "##############################################################################";
    qDebug() << "## Duração total dos testes: 120 segundos (timeout)                         ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## a) Certifique-se de que todas as ECUs estejam conectadas                 ##";
    qDebug() << "## b) Certifique que o cabo USB tipo B esteja conectado                     ##";
    qDebug() << "## c) Certifique que o cabo conversor USB-TTL PL2303HX esteja conectado     ##";
    qDebug() << "## d) Pressione os botões quando solicitado (timeout = 5s)                  ##";
        qDebug() << "## e) Gire completamente todos os potenciometros (timeout = 20s)            ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "## 1  - Iniciar                      r  - Retornar                          ##";
    qDebug() << "##                                                                          ##";
    qDebug() << "##############################################################################";
    qDebug() << "";
    qDebug() << ">> ";
}
