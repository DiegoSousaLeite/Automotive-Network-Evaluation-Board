#ifndef ECU3BOARD_H
#define ECU3BOARD_H

#include "Board.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "Environment.h"

class Ecu3Board : public Board {
private:
    static Ecu3Board* instance;

    // Construtor privado para evitar instanciação externa.
    Ecu3Board();

public:
    // Destruidor
    virtual ~Ecu3Board();

    // Método para acessar a instância singleton.
    static Ecu3Board* getInstance();

    // Impedir cópia e atribuição.
    Ecu3Board(const Ecu3Board&) = delete;
    Ecu3Board& operator=(const Ecu3Board&) = delete;
};

#endif // ECU3BOARD_H
