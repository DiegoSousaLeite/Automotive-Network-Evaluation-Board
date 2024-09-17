#ifndef ECUFRAMECONTROLLER_H
#define ECUFRAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include "FrameController.h"
#include "CmdMessageConstants.h"
#include "ErrorCodeInterface.h"
#include "EcuBusinessInterface.h"
#include "SerialCommPort.h"
#include "ReportControllerInterface.h"
#include "CommunicationTest.h"
#include "CAN1NetworkTest.h"
#include "CAN2NetworkTest.h"
#include "DigitalInputTest.h"
#include "EcuBusinessController.h"
#include "McuBusinessController.h"

// Classe que controla a execução dos testes e operações relacionados às ECUs (Unidades de Controle Eletrônico)
class EcuFrameController : public FrameController {
    Q_OBJECT

public:
    explicit EcuFrameController(QObject *parent = nullptr); // Construtor que inicializa o controlador com um objeto pai opcional
    ~EcuFrameController(); // Destrutor para limpeza de recursos

    // Métodos para execução de testes específicos
    void executeTest(int test_id, int board_id); // Executa um teste específico em uma placa específica
    void executeTest(int test_id); // Executa um teste em todas as placas
    void executeTestReport(int test_id); // Executa a geração de um relatório de teste específico
    void executeCommunicationTest(); // Executa o teste de comunicação
    void executeCan1NetworkTest(); // Executa o teste da rede CAN1
    void executeCan2NetworkTest(); // Executa o teste da rede CAN2
    void executeDigitalInputTest(); // Executa o teste de entrada digital
    void executeAnalogOutputTest(); // Executa o teste de saída analógica
    void executeLinNetworkTest(); // Executa o teste da rede LIN
    void executeCanInitTest(); // Executa o teste de inicialização CAN
    void executeLoopbackCanTest(); // Executa o teste de loopback CAN
    void executeAnalogInputTest(); // Executa o teste de entrada analógica

    // Métodos para operações específicas relacionadas ao firmware e portas seriais
    void executeFirmwareUpload(int board_id, int processor_id); // Executa o upload de firmware para uma placa e processador específicos
    // void executeFirmwareUpload(int port_id, const QString &pathToHexFile); // Método comentado para upload de firmware via porta serial e arquivo hex
    void setEcuBusinessController(EcuBusinessController bsInterface); // Define o controlador de negócios da ECU
    void executeFindSerialPortTest(); // Executa o teste para encontrar portas seriais
    QVector<SerialCommPort*> getSerialCommPortsInfo(); // Obtém informações sobre as portas de comunicação serial

signals:
    void testFinished(int test_id, int board_id, const QString &message); // Sinal emitido quando um teste é finalizado

private slots:
    void handleTimeout(); // Lida com o que acontece quando ocorre um timeout em um teste

private:
    EcuBusinessController* bsController; // Ponteiro para o controlador de negócios da ECU

    // Métodos privados para configuração e manipulação interna
    void setupModels(); // Configura os modelos necessários para o controlador
    void waitReportTestTimeOut(int test_id, int offset, int board_id); // Aguarda o timeout do relatório de teste

    QTimer timer; // Timer utilizado para controlar o timeout de testes
};

#endif // ECUFRAMECONTROLLER_H
