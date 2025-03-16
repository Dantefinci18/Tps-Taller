#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#define CONEXION_CERRADA -1

#include <string>
#include <vector>

#include <stdint.h>

#include "common_duckgame.h"
#include "common_socket.h"

class ProtocoloServidor {
private:
    Socket skt_servidor;
    Socket conexion_cliente;
    DuckGame duckgame;

    bool enviar_arma(const char* arma);
    bool enviar_numero(uint8_t num);

public:
    explicit ProtocoloServidor(const char* nombre_servidor);

    /*
    El envio de strings, con el siguiente formato:
        - 2 bytes sin signo en formato big endian, indicando el largo del string. (sz)
        - La tira de bytes del string, sin contar el terminador de palabra (‘\0’) (mensaje)
    */

    bool enviar_mensaje(const uint16_t sz, const char* mensaje);

    /*
    Devuelve 0 si salio todo OK
    Devuelve -1 si se cerro la conexion
    Devuelve 1 si hubo un error de lectura
    */
    int realizar_orden_de_compra(std::vector<std::string>* operaciones);

    bool enviar_equipamiento();
};

#endif
