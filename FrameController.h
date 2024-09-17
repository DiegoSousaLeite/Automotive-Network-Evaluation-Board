#ifndef FRAMECONTROLLER_H
#define FRAMECONTROLLER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "JigaTestInterface.h"
#include "CmdMessageConstants.h"
#include "ReportControllerInterface.h"
#include "RepBusinessController.h"
#include "TestReportModel.h"
#include "AnalogInputTest.h"
#include "AnalogOutputTest.h"
#include "CAN1NetworkTest.h"
#include "CAN2NetworkTest.h"
#include "CommunicationTest.h"
#include "DigitalInputTest.h"
#include "MCUFirmwareUpload.h"
#include "ecufirmwareupload.h"
#include "findserialporttest.h"
#include "LinNetworkTest.h"
#include "CANLoopbackTest.h"
#include "MCUInterfaceTest.h"
#include "CANInitTest.h"
#include "IFrameListener.h"
#include "PropertyChangeListener.h"

// FrameController é uma classe base que fornece funcionalidades comuns para a execução e controle de testes.
// Ela implementa a interface IFrameListener para ouvir e responder a eventos de mudança de estado.
class FrameController : public QObject, public IFrameListener {
    Q_OBJECT

public:
    explicit FrameController(QObject *parent = nullptr); // Construtor que inicializa o controlador de quadro
    virtual ~FrameController(); // Destrutor virtual para garantir a limpeza adequada em subclasses

    // Instâncias dos diferentes modelos de teste
    CommunicationTest *commTestModel;
    DigitalInputTest *diInputModel;
    AnalogInputTest *anInputModel;
    AnalogOutputTest *anOutputModel;
    CANInitTest *canInitModel;
    CANLoopbackTest *lbNetworkModel;
    CAN1NetworkTest *c1NetworkModel;
    CAN2NetworkTest *c2NetworkModel;
    LinNetworkTest *lnNetworkModel;
    MCUFirmwareUpload *mcuFwUpModel;
    ECUFirmwareUpload *ecuFwUpModel;
    FindSerialPortTest *findSerialModel;
    MCUInterfaceTest *mcu1TestModel;

    // Gerenciamento de listeners
    void addChangeListener(IFrameListener* listener) override; // Adiciona um listener para eventos de mudança
    void removeChangeListener(IFrameListener* listener) override; // Remove um listener para eventos de mudança

protected:
    // Métodos protegidos para manipulação de testes
    void resetTestModel(int test_id); // Reseta o modelo de teste baseado no ID do teste
    void addHeaderTestMessage(int test_id, int board_id, const QString &testMessage); // Adiciona uma mensagem de cabeçalho ao teste
    void waitReportTestTimeout(int test_id, int offset); // Aguarda um tempo limite para o relatório do teste
    // virtual void executeFirmwareUpload(int board_id) = 0; // Método virtual puro para execução de upload de firmware, descomentável em subclasses
    // void addFrameView(RCFrame *jigaFrame); // Método para adicionar uma visualização do quadro, atualmente comentado
    void setReportController(RepBusinessController *rpController); // Define o controlador de relatórios
    RepBusinessController *rpController; // Ponteiro para o controlador de relatórios
    // RCFrame *jigaFrame; // Ponteiro para o quadro de visualização, atualmente comentado
    void handleTimeout(); // Manipula o evento de timeout

    // Adiciona modelos de relatório de teste e conecta seus sinais de atualização
    void addTestReportModels(const QList<TestReportModel*>& models);

private:
    QList<IFrameListener*> listeners; // Lista de listeners para eventos de mudança

public slots:
    void onReportUpdated(const QString &message); // Slot para tratar atualizações de relatórios

protected slots:
    // virtual void propertyChange() = 0; // Método virtual puro para tratar mudanças de propriedade, descomentável em subclasses
};

#endif // FRAMECONTROLLER_H
