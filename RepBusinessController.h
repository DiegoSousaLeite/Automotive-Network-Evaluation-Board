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

class RepBusinessController : public BusinessController,public TimeOutListener  {
    Q_OBJECT

public:
    explicit RepBusinessController(QObject *parent = nullptr);
    void setReportProperty(const QMap<QString, QString>& propFile);
    QString getReportProperty(const QString& key) const;
    void startTestResultMonitor(int testId, int boardId);
    void getTestResult(int testId, int boardId) override;
    void showCommunicationTestReport();
    void showDigitalInputTestReport();
    void showAnalogInputTestReport();
    void showAnalogOutputTestReport();
    void showCanInitTestReport();
    void showCanLoopbackTestReport();
    void showCan1NetworkTestReport();
    void showCan2NetworkTestReport();
    void showLinNetworkTestReport();

private:
    void checkDigitalInputReport(int boardId, const QString &recvStr);
    void checkAnalogInputReport(int boardId, const QString &recvStr);
    void checkAnalogOutputReport(int boardId, const QString &recvStr);
    void checkCanInitNetworkReport(int board_id, const QString& recvStr);
    void checkLBCanNetworkReport(int boardId, const QString &recvStr);
    void checkC1CanNetworkReport(int boardId, const QString &recvStr);
    void checkC2CanNetworkReport(int boardId, const QString &recvStr);
    void checkLinNetworkReport(int boardId, const QString &recvStr);
    void checkMcuGetCanBusReport(const QString &recvStr);


    QMap<QString, QString> reportProperties;

};

#endif // REPBUSINESSCONTROLLER_H
