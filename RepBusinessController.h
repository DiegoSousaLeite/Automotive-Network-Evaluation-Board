#ifndef REPBUSINESSCONTROLLER_H
#define REPBUSINESSCONTROLLER_H

#include "BusinessController.h"
#include <QMap>
#include "Board.h"
#include "PersistenceController.h"

class RepBusinessController : public BusinessController {
    Q_OBJECT

public:
    explicit RepBusinessController(QObject *parent = nullptr);
    void startTestResultMonitor(int testId, int boardId);
    void getTestResult(int testId, int boardId);

private:
    void checkDigitalInputReport(int boardId, const QString &recvStr);
    void checkAnalogInputReport(int boardId, const QString &recvStr);
    void checkAnalogOutputReport(int boardId, const QString &recvStr);
    void checkLBCanNetworkReport(int boardId, const QString &recvStr);
    void checkC1CanNetworkReport(int boardId, const QString &recvStr);
    void checkC2CanNetworkReport(int boardId, const QString &recvStr);
    void checkLinNetworkReport(int boardId, const QString &recvStr);
    void checkMcuGetCanBusReport(const QString &recvStr);
    void addCmdTestMessage(int testId, int boardId, const QString &testMessage, bool header);

    PersistenceController *psController;
    QMap<int, Board*> boardList;
};

#endif // REPBUSINESSCONTROLLER_H
