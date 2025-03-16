#ifndef CLIENT_CLIENTE_H
#define CLIENT_CLIENTE_H

#include "client_protocolo.h"
#include "common_socket.h"

class Cliente {
private:
    Socket conexion;
    ProtocoloCliente protocolo;

public:
    explicit Cliente(const char* nombre_host, const char* nombre_servidor);

    void run();
};

#endif
