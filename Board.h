#ifndef BOARD_H
#define BOARD_H

#include <QString>
#include <QDebug>
#include "SerialCommPort.h"
#include "JigaTestInterface.h"

class Board {
private:
    int board_id;
    int commPort_id;
    int canbus;
    QString description;
    int baudrate;
    SerialCommPort serialCommPort;

public:
    // Constructor
    Board();

    void setBoardIdentification(int board_id);
    int getBoardIdentification() const;

    void setBoardDescription(const QString& board_description);
    QString getBoardDescription() const;

    void setCommPortName(const QString& commPort);
    QString getCommPortName() const;

    void setCommPortIdentification(int commPortID);
    int getCommPortIdentification() const;

    void setCanbus(int canbus);
    int getCanbus() const;

    void toggleCanBus();

    void setBoardBaudRate(int baudrate);
    int getBoardBaudRate() const;

    void printBoardInformation() const;

    SerialCommPort& getSerialCommPort();
    const SerialCommPort& getSerialCommPort() const;

    void resetBoardData();
};

#endif // BOARD_H
