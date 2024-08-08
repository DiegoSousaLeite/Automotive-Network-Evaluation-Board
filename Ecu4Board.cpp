#include "Ecu4Board.h"

// Inicialização da instância estática
Ecu4Board* Ecu4Board::instance = nullptr;

Ecu4Board::Ecu4Board() {
    int ecuBaudRate = Environment::getInt("ecu.app.baudrate", 115200);
    setBoardIdentification(JigaTestInterface::ECU4_BOARD_ID);
    setBoardDescription("ECU4");
    setBoardBaudRate(ecuBaudRate);
}

Ecu4Board::~Ecu4Board() {
    // Aqui você pode adicionar código para limpeza se necessário
}

Ecu4Board* Ecu4Board::getInstance() {
    if (!instance) {
        instance = new Ecu4Board();
    }
    return instance;
}
