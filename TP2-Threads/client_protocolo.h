#ifndef CLIENT_PROTOCOLO_H
#define CLIENT_PROTOCOLO_H

#define ERROR_DE_LECTURA -1

#include <array>
#include <string>
#include <vector>

#include <stdint.h>

#include "common_protocolo.h"
#include "common_socket.h"

class ProtocoloCliente: public Protocolo {
private:
    std::string obtener_premio(uint8_t reward_id);
    std::string recibir_recoleccion_de_premio();

public:
    explicit ProtocoloCliente(Socket&& conexion);

    /*devuelve false si hubo un error

    Protocolo : 0x03 <player-name> <box-id> donde 0x03 es un byte con el número literal 0x03,
    <nombre> es un entero de dos bytes en big endian con el largo del nombre en ASCII, seguido
    con el nombre del jugador, y <box-id> es un byte con el id de la caja a recoger (0x01, 0x02,
    0x03 o 0x04).*/
    bool recoger_caja(const std::string& nombre, uint8_t box_id);

    std::vector<std::string> recibir_mensajes(int n);
};

#endif
