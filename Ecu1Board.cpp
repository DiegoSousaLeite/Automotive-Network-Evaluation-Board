#include "Ecu1Board.h"

// Inicialização da instância estática
Ecu1Board* Ecu1Board::instance = nullptr;

Ecu1Board::Ecu1Board() {
    int ecuBaudRate = Environment::getInt("ecu.app.baudrate", 115200);
    setBoardIdentification(JigaTestConstants::ECU1_BOARD_ID);
    setBoardDescription("ECU1");
    setBoardBaudRate(ecuBaudRate);
}

Ecu1Board::~Ecu1Board() {
    // Implementação do destruidor se necessário
}

Ecu1Board* Ecu1Board::getInstance() {
    if (!instance) {
        instance = new Ecu1Board();
    }
    return instance;
}
