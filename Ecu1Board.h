#ifndef ECU1BOARD_H
#define ECU1BOARD_H

#include "Board.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "Environment.h"

class Mcu1Board : public Board {
private:
    static Mcu1Board* instance;

    // Constructor privado para evitar instanciação externa.
    Mcu1Board() {
        int ecuBaudRate = Environment::getInt(SystemProperties::ECU_APP_BAUDRATE.c_str(),115200);
        setBoardIdentification(JigaTestConstants::ECU1_BOARD_ID);
        setBoardDescription("ECU1");
        setBoardBaudRate(ecuBaudRate);
    }

public:
    // Destructor
    virtual ~Mcu1Board() {}

    // Método para acessar a instância singleton.
    static Mcu1Board* getInstance() {
        if (!instance) {
            instance = new Mcu1Board();
        }
        return instance;
    }

    // Impedir cópia e atribuição.
    Mcu1Board(const Mcu1Board&) = delete;
    Mcu1Board& operator=(const Mcu1Board&) = delete;
};

// Inicialização da instância estática
Mcu1Board* Mcu1Board::instance = nullptr;

#endif // ECU1BOARD_H
