#ifndef CLIENT_CLIENTE_H
#define CLIENT_CLIENTE_H

#include "client_protocolo.h"

class Cliente {
private:
    ProtocoloCliente protocolo;

public:
    explicit Cliente(const char* nombre_host, const char* nombre_servidor);

    int run();
};

#endif
