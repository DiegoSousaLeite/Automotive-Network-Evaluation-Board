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
    void startTestResultMonitor(int testId, int boardId);
    void getTestResult(int testId, int boardId) override;
    void showCommTestReport();

private:
    void checkDigitalInputReport(int boardId, const QString &recvStr);
    void checkAnalogInputReport(int boardId, const QString &recvStr);
    void checkAnalogOutputReport(int boardId, const QString &recvStr);
    void checkLBCanNetworkReport(int boardId, const QString &recvStr);
    void checkC1CanNetworkReport(int boardId, const QString &recvStr);
    void checkC2CanNetworkReport(int boardId, const QString &recvStr);
    void checkLinNetworkReport(int boardId, const QString &recvStr);
    void checkMcuGetCanBusReport(const QString &recvStr);

    PersistenceController *psController;
    QMap<int, Board*> boardList;
};

#endif // REPBUSINESSCONTROLLER_H
