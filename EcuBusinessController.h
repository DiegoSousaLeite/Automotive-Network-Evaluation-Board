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
class EcuBusinessController : public BusinessController
{
    Q_OBJECT

public:
    explicit EcuBusinessController(QObject *parent = nullptr);
    bool startIndividualBoardTest(int testId, int boardId);
    int loadBoard(int testId, int boardId);
    int loadAllBoards(int testId);
    bool loadSerialCommPort(int boardId);
    int loadAllSerialCommPorts();
    void setReportController(RepBusinessController *rpController);
    int uploadFirmware(int boardId);
    int uploadFirmware(int portId, const QString &pathToHexFile);
    QVector<SerialCommPort*> getSerialCommPortsInfo();

private:

    RepBusinessController *repController;
    bool startTestExecution(int testId, int boardId);
};

#endif // ECUBUSINESSCONTROLLER_H
