#ifndef ECU4BOARD_H
#define ECU4BOARD_H

#include "Board.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "Environment.h"

class Ecu4Board : public Board {
private:
    static Ecu4Board* instance;

    // Construtor privado para evitar instanciação externa.
    Ecu4Board();

public:
    // Destruidor
    virtual ~Ecu4Board();

    // Método para acessar a instância singleton.
    static Ecu4Board* getInstance();

    // Impedir cópia e atribuição.
    Ecu4Board(const Ecu4Board&) = delete;
    Ecu4Board& operator=(const Ecu4Board&) = delete;
};

#endif // ECU4BOARD_H
