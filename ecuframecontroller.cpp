#include "ecuframecontroller.h"
#include <QDebug>

EcuFrameController::EcuFrameController(QObject *parent) : FrameController(parent) {
    connectSignals();
}

void EcuFrameController::connectSignals() {
    // Exemplo: conectar sinais de modelos a slots para manipular mudanças
}

void EcuFrameController::executeTest(int testId, int boardId) {
    QString testMessage;
    if(boardId == MCU1_BOARD_ID){
        testMessage = " iniciada!";
    } else {
        testMessage = " iniciado!";
    }

    qDebug() << "Teste" << testId << "para o board" << boardId << testMessage;

    // Implementação específica para iniciar o teste
}

void EcuFrameController::executeTest(int testId) {
    QString testMessage = "Teste iniciado!";
    qDebug() << testMessage;

    // Dependendo do teste, a execução específica é chamada
    switch(testId) {
    case ANALOG_OUTPUT_TEST:
        executeAnalogOutputTest();
        break;
    case LIN_NETWORK_TEST:
        executeLinNetworkTest();
        break;
    // Adicione casos adicionais conforme necessário
    default:
        qDebug() << "Teste não implementado";
    }
}

void EcuFrameController::executeAnalogOutputTest() {
    // Simulação de um teste de saída analógica
    qDebug() << "Executando teste de saída analógica";
}

void EcuFrameController::executeLinNetworkTest() {
    // Simulação de um teste de rede LIN
    qDebug() << "Executando teste de rede LIN";
}

void EcuFrameController::setEcuBusinessController(EcuBusinessInterface* bsInterface) {
    if (bsController != bsInterface) {
        bsController = bsInterface;
        // Potencialmente desconectar sinais antigos e conectar novos se necessário
    }
}

void EcuFrameController::propertyChange(PropertyChangeEvent evt) {
    // Adaptar esta função para ser um slot que reage a sinais Qt
    qDebug() << "Propriedade mudou:" << evt.propertyName();
}

// Outros métodos necessários podem ser implementados aqui

