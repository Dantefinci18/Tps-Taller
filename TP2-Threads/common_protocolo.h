#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <string>

#include "common_socket.h"

class Protocolo {
protected:
    Socket conexion;
    bool was_closed = false;

protected:
    bool enviar_nombre(const std::string& nombre);

    std::string recibir_nombre();

public:
    explicit Protocolo(Socket&&);
};

#endif
