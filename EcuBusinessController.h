#ifndef ECUBUSINESSCONTROLLER_H
#define ECUBUSINESSCONTROLLER_H

#include <QObject>
#include "PersistenceController.h"
#include "SystemDefinition.h"
#include "RepBusinessController.h"
#include "BusinessController.h"
#include "JigaTestInterface.h"

class EcuBusinessController : public BusinessController
{
    Q_OBJECT

public:
    explicit EcuBusinessController(QObject *parent = nullptr);
    bool startIndividualBoardTest(int test_id, int board_id);
    int loadBoard(int test_id, int board_id);
    int loadAllBoards(int test_id);
    bool loadSerialCommPort(int board_id);
    int loadAllSerialCommPorts();
    bool setReportController(RepBusinessController *rpController);
    int uploadFirmware(int board_id);
    static void main(int argc, char *argv[]);

private:

    RepBusinessController *repController;
    bool startTestExecution(int test_id, int board_id);
};

#endif // ECUBUSINESSCONTROLLER_H
