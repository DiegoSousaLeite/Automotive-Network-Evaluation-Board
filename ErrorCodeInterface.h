#ifndef ERRORCODEINTERFACE_H
#define ERRORCODEINTERFACE_H

class ErroCodeInterface {
public:
    static constexpr int SUCCESS              = 0;
    static constexpr int ERR_PORT_NOT_FOUND   = 1;
    static constexpr int ERR_PORT_NOT_OPPENED = 2;
    static constexpr int ERR_BOARD_NOT_ACK    = 3;

};

#endif // ERRORCODEINTERFACE_H
