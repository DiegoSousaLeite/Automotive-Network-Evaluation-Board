#ifndef ECU2BOARD_H
#define ECU2BOARD_H

#include "Board.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "Environment.h"

class Ecu2Board : public Board {
private:
    static Ecu2Board* instance;

    // Constructor privado para evitar instanciação externa.
    Ecu2Board();

public:
    // Destructor
    virtual ~Ecu2Board();

    // Método para acessar a instância singleton.
    static Ecu2Board* getInstance();

    // Impedir cópia e atribuição.
    Ecu2Board(const Ecu2Board&) = delete;
    Ecu2Board& operator=(const Ecu2Board&) = delete;
};

#endif // ECU2BOARD_H
