#include "Ecu3Board.h"

// Inicialização da instância estática
Ecu3Board* Ecu3Board::instance = nullptr;

Ecu3Board::Ecu3Board() {
    int ecuBaudRate = Environment::getInt("ecu.app.baudrate", 115200);
    setBoardIdentification(JigaTestConstants::ECU3_BOARD_ID);
    setBoardDescription("ECU3");
    setBoardBaudRate(ecuBaudRate);
}

Ecu3Board::~Ecu3Board() {
    // Limpeza necessária, se houver
}

Ecu3Board* Ecu3Board::getInstance() {
    if (!instance) {
        instance = new Ecu3Board();
    }
    return instance;
}
