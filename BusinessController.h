#ifndef BUSINESSCONTROLLER_H
#define BUSINESSCONTROLLER_H

#include <QObject>
#include <QList>
#include <QThread>
#include "Board.h"
#include "PersistenceController.h"
#include "EcuBusinessInterface.h"
#include "McuBusinessInterface.h"
#include "CommunicationTest.h"
#include "MCUFirmwareUpload.h"
#include "DigitalInputTest.h"
#include "AnalogInputTest.h"
#include "AnalogOutputTest.h"
#include "CANInitTest.h"
#include "CANLoopbackTest.h"
#include "CAN1NetworkTest.h"
#include "CAN2NetworkTest.h"
#include "LinNetworkTest.h"
#include "MCUInterfaceTest.h"
#include <QEventLoop>
#include <QTimer>
#include <QStringView>
#include "ecufirmwareupload.h"

// BusinessController é responsável por gerenciar a lógica de negócios para operações relacionadas a ECUs e MCUs.
// Ele herda das interfaces McuBusinessInterface e EcuBusinessInterface, fornecendo a implementação dessas interfaces.
class BusinessController : public QObject, public virtual McuBusinessInterface, public virtual EcuBusinessInterface {
    Q_OBJECT

public:
    explicit BusinessController(QObject *parent = nullptr); // Construtor que inicializa o controlador
    void setPersistenceController(PersistenceController *controller); // Define o controlador de persistência

    // Modelos de teste utilizados pelo controlador
    CommunicationTest *commTestModel;
    ECUFirmwareUpload *ecuFwUpModel;
    DigitalInputTest *diInputModel;
    AnalogInputTest *anInputModel;
    AnalogOutputTest *anOutputModel;
    CANInitTest *canInitModel;
    CANLoopbackTest *canLoopbackModel;
    CAN1NetworkTest *c1NetworkModel;
    CAN2NetworkTest *c2NetworkModel;
    LinNetworkTest *lnNetworkModel;
    MCUInterfaceTest *mcu1InterModel;

    QList<Board *> boardList; // Lista de placas sob controle
    PersistenceController *psController; // Controlador de persistência

    // Adiciona uma mensagem de comando ao teste, implementando o método da interface
    void addCmdTestMessage(int testId, int boardId, const QString &testMessage, bool header) override;

protected:
    // Envia um comando AT para a placa especificada
    void sendAtCommand(int testId, int boardId, const QString &atCommand);
    // Aguarda e verifica a resposta para um comando AT enviado
    bool acknowledgeAtCommand(int testId, int boardId);
    // Extrai e obtém o código do relatório de teste da string recebida
    int getTestReportCode(const QString &recvStr);
};

#endif // BUSINESSCONTROLLER_H
