#ifndef ECUBUSINESSCONTROLLER_H
#define ECUBUSINESSCONTROLLER_H

#include <QObject>
#include "PersistenceController.h"
#include "SystemDefinition.h"
#include "RepBusinessController.h"
#include "BusinessController.h"
#include "JigaTestInterface.h"
#include "ErrorCodeInterface.h"
#include "atCommandConstants.h"
#include <QSerialPortInfo>

// A classe EcuBusinessController herda de BusinessController e gerencia a execução de testes e operações nas ECUs (Unidades de Controle Eletrônico).
class EcuBusinessController : public BusinessController
{
    Q_OBJECT

public:
    explicit EcuBusinessController(QObject *parent = nullptr); // Construtor que inicializa o controlador
    bool startIndividualBoardTest(int testId, int boardId); // Inicia um teste individual em uma placa específica
    int loadBoard(int testId, int boardId); // Carrega uma placa específica para testes
    int loadAllBoards(int testId); // Carrega todas as placas disponíveis para testes
    bool loadSerialCommPort(int boardId); // Carrega a porta de comunicação serial de uma placa específica
    int loadSerialCommPorts(); // Carrega todas as portas de comunicação serial disponíveis
    void setReportController(RepBusinessController *rpController); // Define o controlador de relatórios
    int uploadFirmware(int boardId, int processorId); // Faz upload do firmware para uma placa específica
    QVector<SerialCommPort*> getSerialCommPortsInfo(); // Obtém informações sobre as portas de comunicação serial
    int findSerialCommPorts(); // Encontra e retorna todas as portas de comunicação serial disponíveis

private:
    RepBusinessController *repController; // Ponteiro para o controlador de relatórios
    bool startTestExecution(int testId, int boardId); // Método auxiliar para iniciar a execução de um teste
};

#endif // ECUBUSINESSCONTROLLER_H
