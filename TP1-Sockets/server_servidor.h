#ifndef SERVER_SERVIDOR_H
#define SERVER_SERVIDOR_H

#include "server_protocolo.h"

class Servidor {
private:
    ProtocoloServidor protocolo;

public:
    explicit Servidor(const char* nombre_servidor);
    int run();
};

#endif
