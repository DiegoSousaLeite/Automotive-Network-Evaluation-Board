#include "Ecu2Board.h"

// Inicialização da instância estática
Ecu2Board* Ecu2Board::instance = nullptr;

Ecu2Board::Ecu2Board() {
    int ecuBaudRate = Environment::getInt("ecu.app.baudrate", 115200);
    setBoardIdentification(JigaTestInterface::ECU2_BOARD_ID);
    setBoardDescription("ECU2");
    setBoardBaudRate(ecuBaudRate);
}

Ecu2Board::~Ecu2Board() {
    // Implementação do destruidor se necessário
}

Ecu2Board* Ecu2Board::getInstance() {
    if (!instance) {
        instance = new Ecu2Board();
    }
    return instance;
}
