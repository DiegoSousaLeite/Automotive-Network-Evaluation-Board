#ifndef ECUBUSINESSINTERFACE_H
#define ECUBUSINESSINTERFACE_H

#include <QString>
#include "SerialCommPort.h"

class EcuBusinessInterface
{
public:
    virtual ~EcuBusinessInterface() {}

    static const int ECU1_OK_CODE = 10;
    static const int ECU2_OK_CODE = 11;
    static const int ECU3_OK_CODE = 12;
    static const int ECU4_OK_CODE = 13;
    static const int MCU1_OK_CODE = 14;

    // Error codes
    static const int INVALID_ECU_TEST               = -2;
    static const int ERROR_INVALID_SERIAL_PORT      = -3;
    static const int ERROR_UNAVAILABLE_SERIAL_PORT  = -4;
    static const int ERROR_TO_START_TEST            = -5;
    static const int ERROR_COMMUNICATION_TEST       = -5;
    static const int ERROR_RETRIEVE_REPORT_CODE     = -5;
    static const int SUCCESS_COMMUNICATION_TEST     = 0;

    static const int SUCCESS_START_TEST  = 0;
    static const int MAX_NUMBER_ATTEMPTS = 5;

    //a "interface" em C++ é criada através de uma classe abstrata pura.
    //Métodos virtuais puros (denotados com = 0) precisam ser implementados por qualquer classe que herde desta "interface".
//    virtual bool startIndividualBoardTest(int test_id, int board_id) = 0;
//    virtual int loadBoard(int test_id, int board_id) = 0;
//    virtual int loadAllBoards(int test_id) = 0;
//    virtual bool loadSerialCommPort(int board_id) = 0;
//    virtual QVector<SerialCommPort*> getSerialCommPortsInfo() = 0;
//    virtual int loadAllSerialCommPorts() = 0;
//    virtual int uploadFirmware(int board_id) = 0;
//    virtual int uploadFirmware(int port_id, const QString &pathToFile) = 0;
   virtual void addCmdTestMessage(int test_id, int board_id, const QString &testMessage, bool header) = 0;
};

#endif // ECUBUSINESSINTERFACE_H
