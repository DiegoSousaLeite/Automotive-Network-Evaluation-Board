#ifndef REPBUSINESSCONTROLLER_H
#define REPBUSINESSCONTROLLER_H

#include "BusinessController.h"
#include <QMap>
#include "Board.h"
#include "PersistenceController.h"
#include "TimeOutListener.h"
#include "TimeOutMonitor.h"
#include "EcuBusinessInterface.h"
#include "CmdMessageConstants.h"

// A classe RepBusinessController herda de BusinessController e TimeOutListener
// Ela gerencia os relatórios de teste e monitoramento de resultados para diferentes tipos de testes em placas ECU.
class RepBusinessController : public BusinessController, public TimeOutListener {
    Q_OBJECT

public:
    // Construtor explícito da classe, recebe um QObject opcional como pai
    explicit RepBusinessController(QObject *parent = nullptr);

    // Define as propriedades do relatório usando um mapa de strings
    void setReportProperty(const QMap<QString, QString>& propFile);

    // Obtém uma propriedade específica do relatório com base na chave fornecida
    QString getReportProperty(const QString& key) const;

    // Inicia o monitoramento do resultado do teste para um teste específico e uma placa específica
    void startTestResultMonitor(int testId, int boardId);

    // Obtém o resultado do teste para um teste e uma placa específica, sobrescreve o método da classe base
    void getTestResult(int testId, int boardId) override;

    // Gera e exibe relatórios de teste de comunicação
    void showCommunicationTestReport();

    // Gera e exibe relatórios de teste para entradas digitais
    void showDigitalInputTestReport();

    // Gera e exibe relatórios de teste para entradas analógicas
    void showAnalogInputTestReport();

    // Gera e exibe relatórios de teste para saídas analógicas
    void showAnalogOutputTestReport();

    // Gera e exibe relatórios de teste para inicialização CAN
    void showCanInitTestReport();

    // Gera e exibe relatórios de teste para loopback CAN
    void showCanLoopbackTestReport();

    // Gera e exibe relatórios de teste para a rede CAN1
    void showCan1NetworkTestReport();

    // Gera e exibe relatórios de teste para a rede CAN2
    void showCan2NetworkTestReport();

    // Gera e exibe relatórios de teste para a rede LIN
    void showLinNetworkTestReport();

private:
    // Funções privadas para verificar resultados de diferentes testes e gerar relatórios correspondentes
    void checkDigitalInputReport(int boardId, const QString &recvStr);
    void checkAnalogInputReport(int boardId, const QString &recvStr);
    void checkAnalogOutputReport(int boardId, const QString &recvStr);
    void checkCanInitNetworkReport(int board_id, const QString& recvStr);
    void checkLBCanNetworkReport(int boardId, const QString &recvStr);
    void checkC1CanNetworkReport(int boardId, const QString &recvStr);
    void checkC2CanNetworkReport(int boardId, const QString &recvStr);
    void checkLinNetworkReport(int boardId, const QString &recvStr);
    void checkMcuGetCanBusReport(const QString &recvStr);

    // Mapa para armazenar propriedades do relatório
    QMap<QString, QString> reportProperties;
};

#endif // REPBUSINESSCONTROLLER_H
