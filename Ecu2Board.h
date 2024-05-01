#ifndef ECU2BOARD_H
#define ECU2BOARD_H

#include "Board.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "Environment.h"

class Ecu2Board : public Board{
private:

    static Ecu2Board* instance;

    // Constructor privado para evitar instanciação externa.
    Ecu2Board() {
        int ecuBaudRate = Environment::getInt(SystemProperties::ECU_APP_BAUDRATE.c_str(),115200);
        setBoardIdentification(JigaTestConstants::ECU2_BOARD_ID);
        setBoardDescription("ECU2");
        setBoardBaudRate(ecuBaudRate);
    }

public:
    // Destructor
    virtual ~Ecu2Board() {}

    // Método para acessar a instância singleton.
    static Ecu2Board* getInstance() {
        if (!instance) {
            instance = new Ecu2Board();
        }
        return instance;
    }

    // Impedir cópia e atribuição.
    Ecu2Board(const Ecu2Board&) = delete;
    Ecu2Board& operator=(const Ecu2Board&) = delete;

};
//Inicialização da instância estática
Ecu2Board* Ecu2Board::instance = nullptr;

#endif // ECU2BOARD_H
