#include "Board.h"

// Constructor
Board::Board() : board_id(-1), commPort_id(-1), canbus(-1), baudrate(115200) {
}

void Board::setBoardIdentification(int board_id) {
    this->board_id = board_id;
}

int Board::getBoardIdentification() const {
    return board_id;
}

void Board::setBoardDescription(const QString& board_description) {
    this->description = board_description;
}

QString Board::getBoardDescription() const {
    return description;
}

//void Board::setCommPortName(const QString& commPort) {
//    serialCommPort.setSystemPortName(commPort);
//}

//QString Board::getCommPortName() const {
//    return serialCommPort.getSystemPortName();
//}

//void Board::setCommPortIdentification(int commPortID) {
//    this->commPort_id = commPortID;
//}

//int Board::getCommPortIdentification() const {
//    return commPort_id;
//}

void Board::setCanbus(int canbus) {
    if (board_id == JigaTestInterface::ECU1_BOARD_ID || board_id == JigaTestInterface::ECU2_BOARD_ID) {
        this->canbus = (board_id == JigaTestInterface::ECU1_BOARD_ID) ? JigaTestInterface::ECU_CANBUS_1 : JigaTestInterface::ECU_CANBUS_2;
    } else {
        this->canbus = canbus;
    }
}

int Board::getCanbus() const {
    return canbus;
}

void Board::toggleCanBus() {
    if (board_id == JigaTestInterface::ECU3_BOARD_ID || board_id == JigaTestInterface::ECU4_BOARD_ID) {
        canbus = (canbus == JigaTestInterface::ECU_CANBUS_1) ? JigaTestInterface::ECU_CANBUS_2 : JigaTestInterface::ECU_CANBUS_1;
    }
}

void Board::setBoardBaudRate(int baudrate) {
    this->baudrate = baudrate;
}

int Board::getBoardBaudRate() const {
    return baudrate;
}

void Board::printBoardInformation() const {
    qDebug() << "Board";
    qDebug() << ":id=" << this->board_id;
    qDebug() << ":desc=" << this->description;
    qDebug() << ":can=" << this->canbus;
    this->serialCommPort.printSerialCommPortInfo();
}

SerialCommPort& Board::getSerialCommPort() {
    return serialCommPort;
}

const SerialCommPort& Board::getSerialCommPort() const {
    return serialCommPort;
}

void Board::resetBoardData()
{
    serialCommPort.init();
}
