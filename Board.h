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
    Board() : board_id(-1), commPort_id(-1), canbus(-1), baudrate(115200) {
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

        if (board_id == JigaTestConstants::ECU1_BOARD_ID || board_id == JigaTestConstants::ECU2_BOARD_ID) {
            this->canbus = (board_id == JigaTestConstants::ECU1_BOARD_ID) ? JigaTestConstants::ECU_CANBUS_1 : JigaTestConstants::ECU_CANBUS_2;
        } else {
            this->canbus = canbus;
        }
    }

    int getCanbus() const {
        return canbus;
    }

    void toggleCanBus() {
        if (board_id == JigaTestConstants::ECU3_BOARD_ID || board_id == JigaTestConstants::ECU4_BOARD_ID) {
            canbus = (canbus == JigaTestConstants::ECU_CANBUS_1) ? JigaTestConstants::ECU_CANBUS_2 : JigaTestConstants::ECU_CANBUS_1;
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
