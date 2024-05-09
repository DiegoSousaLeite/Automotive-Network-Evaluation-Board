#ifndef ECUBUSINESSCONTROLLER_H
#define ECUBUSINESSCONTROLLER_H

#include "PersistenceController.h"
#include "BusinessController.h"
#include "EcuBusinessInterface.h"
#include "atCommandConstants.h"
#include "CmdMessageConstants.h"
#include "JigaTestInterface.h"
#include <QTimer>

class EcuBusinessController : public BusinessController{
    Q_OBJECT

public:
    explicit EcuBusinessController(QObject *parent = nullptr);
    bool startIndividualBoardTest(int testId, int boardId);
    int loadBoard(int testId, int boardId);
    int loadAllBoards(int testId);
    bool loadSerialCommPort(int boardId);
    int loadAllSerialCommPorts();
    int uploadFirmware(int boardId);
    int uploadFirmware(int portId, const QString &pathToHexFile);

private:
    PersistenceController *psController;
    void addCmdTestMessage(int testId, int boardId, const QString &testMessage, bool header);
    bool startTestExecution(int testId, int boardId);
    void setPersistenceController(PersistenceController *controller);

    QTimer retryTimer;
    int currentAttempt;

};

#endif // ECUBUSINESSCONTROLLER_H
