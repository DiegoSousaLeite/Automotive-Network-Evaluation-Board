#ifndef MCU1BOARD_H
#define MCU1BOARD_H

#include "Board.h"
#include "JigaTestInterface.h"
#include "SystemProperties.h"
#include "Environment.h"

class Mcu1Board : public Board {
private:
    static Mcu1Board* instance;

    // Construtor privado para evitar instanciação externa.
    Mcu1Board();

public:
    // Destruidor
    virtual ~Mcu1Board();

    // Método para acessar a instância singleton.
    static Mcu1Board* getInstance();

    // Impedir cópia e atribuição.
    Mcu1Board(const Mcu1Board&) = delete;
    Mcu1Board& operator=(const Mcu1Board&) = delete;
};

#endif // MCU1BOARD_H
