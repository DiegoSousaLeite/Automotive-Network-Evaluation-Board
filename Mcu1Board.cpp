#include "Mcu1Board.h"

// Inicialização da instância estática
Mcu1Board* Mcu1Board::instance = nullptr;

Mcu1Board::Mcu1Board() {
    int ecuBaudRate = Environment::getInt("ecu.app.baudrate", 115200);
    setBoardIdentification(JigaTestConstants::MCU1_BOARD_ID);
    setBoardDescription("MCU1");
    setBoardBaudRate(ecuBaudRate);
}

Mcu1Board::~Mcu1Board() {
    // Aqui você pode adicionar código para limpeza se necessário
}

Mcu1Board* Mcu1Board::getInstance() {
    if (!instance) {
        instance = new Mcu1Board();
    }
    return instance;
}
