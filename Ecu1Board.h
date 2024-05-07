#ifndef ECU1BOARD_H
#define ECU1BOARD_H

#include "Board.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "Environment.h"

class Ecu1Board : public Board {
private:
    static Ecu1Board* instance;

    // Constructor privado para evitar instanciação externa.
    Ecu1Board();

public:
    // Destructor
    virtual ~Ecu1Board();

    // Método para acessar a instância singleton.
    static Ecu1Board* getInstance();

    // Impedir cópia e atribuição.
    Ecu1Board(const Ecu1Board&) = delete;
    Ecu1Board& operator=(const Ecu1Board&) = delete;
};

#endif // ECU1BOARD_H
