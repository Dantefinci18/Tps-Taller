#ifndef CLIENT_PROTOCOLO_H
#define CLIENT_PROTOCOLO_H

#define ERROR_DE_LECTURA -1

#include <array>
#include <string>
#include <vector>

#include <stdint.h>

#include "common_socket.h"

class ProtocoloCliente {
private:
    Socket skt_cliente;

    bool recibir_numero(uint8_t* num);

public:
    explicit ProtocoloCliente(const char* nombre_host, const char* nombre_servidor);

    std::vector<char> recibir_mensaje();

    /*
    Las órdenes de compra, que consisten en un arreglo de caracteres en formato ascii de 1 byte
    finalizado por un byte en null(0x00)
    */
    bool enviar_orden_de_compra(const std::string& orden_de_compra);

    // Un entero de 8 bits sin signo para comunicar las municiones de cada arma
    /*uint8_t recibir_informacion_de_municion(const char *arma);

    //Un entero de 8 bits sin signo, 0 si no está equipado el cuchillo, 1 si lo esta
    uint8_t recibir_informacion_de_cuchillo();*/

    bool recibir_informacion_de_eqipamiento(std::array<std::string, 3>* informacion);
};

#endif
