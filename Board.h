#ifndef BOARD_H
#define BOARD_H

#include <QString>
#include "SerialCommPort.h"

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
    Board() : board_id(-1), commPort_id(-1), canbus(-1), baudrate(9600) {
    }

    void setBoardIdentification(int board_id) {
        this->board_id = board_id;
    }

    int getBoardIdentification() const {
        return board_id;
    }

    void setBoardDescription(const QString& board_description) {
        this->description = board_description;
    }

    QString getBoardDescription() const {
        return description;
    }

    void setCommPortName(const QString& commPort) {
        serialCommPort.setSystemPortName(commPort);
    }

    QString getCommPortName() const {
        return serialCommPort.getSystemPortName();
    }

    void setCommPortIdentification(int commPortID) {
        this->commPort_id = commPortID;
    }

    int getCommPortIdentification() const {
        return commPort_id;
    }

    void setCanbus(int canbus) {
        // Assuming these constants are defined elsewhere in your project
        const int ECU_CANBUS_1 = 1;
        const int ECU_CANBUS_2 = 2;

        if (board_id == ECU1_BOARD_ID || board_id == ECU2_BOARD_ID) {
            this->canbus = (board_id == ECU1_BOARD_ID) ? ECU_CANBUS_1 : ECU_CANBUS_2;
        } else {
            this->canbus = canbus;
        }
    }

    int getCanbus() const {
        return canbus;
    }

    void toggleCanBus() {
        if (board_id == ECU3_BOARD_ID || board_id == ECU4_BOARD_ID) {
            canbus = (canbus == ECU_CANBUS_1) ? ECU_CANBUS_2 : ECU_CANBUS_1;
        }
    }

    void setBoardBaudRate(int baudrate) {
        this->baudrate = baudrate;
    }

    int getBoardBaudRate() const {
        return baudrate;
    }

    void printBoardInformation() const {
        qDebug() << "[" << getCommPortIdentification() << "]" << getCommPortName() << ", "
                 << "Board_id = " << getBoardIdentification() << ", "
                 << "Port_desc = " << getBoardDescription();
    }
};

#endif // BOARD_H
