
#define APARECIO_UNA_CAJA 0x0506
#define SE_AGARRO_UN_OBJETO 0x0406

#include "client_protocolo.h"

#include <utility>

#include <arpa/inet.h>

#include "common_retorno.h"
#include "common_rewards_ids.h"


ProtocoloCliente::ProtocoloCliente(Socket&& conexion): Protocolo(std::move(conexion)) {}


bool ProtocoloCliente::recoger_caja(const std::string& nombre, uint8_t box_id) {
    uint8_t byte = 0x03;
    size_t bytes_enviados = conexion.sendall(&byte, sizeof(uint8_t), &was_closed);

    if (was_closed || bytes_enviados < sizeof(uint8_t) || !enviar_nombre(nombre))
        return false;

    bytes_enviados = conexion.sendall(&box_id, sizeof(uint8_t), &was_closed);

    return !(was_closed || bytes_enviados < sizeof(uint8_t));
}


std::string ProtocoloCliente::obtener_premio(uint8_t reward_id) {
    switch (reward_id) {
        case BAZOOKA:
            return "Bazooka";

        case CHAINSAW:
            return "Chainsaw";

        case DEATH_RAY:
            return "Death ray";

        case SHOUTGUN:
            return "Shotgun";
    }

    return "";
}


std::string ProtocoloCliente::recibir_recoleccion_de_premio() {
    std::string nombre = recibir_nombre();

    uint8_t reward_id;
    size_t bytes_leidos = conexion.recvall(&reward_id, sizeof(uint8_t), &was_closed);

    if (was_closed || bytes_leidos < sizeof(uint8_t)) {
        return "";
    }

    std::string premio = obtener_premio(reward_id);

    return nombre + " picked up a " + premio;
}


std::vector<std::string> ProtocoloCliente::recibir_mensajes(int n) {
    std::vector<std::string> mensajes;

    for (int i = 0; i < n; i++) {
        uint16_t primeros_bytes;
        size_t bytes_leidos = conexion.recvall(&primeros_bytes, sizeof(uint16_t), &was_closed);

        if (was_closed || bytes_leidos < sizeof(uint16_t)) {
            mensajes.clear();
            return mensajes;
        }

        if (primeros_bytes == APARECIO_UNA_CAJA) {
            mensajes.push_back("A new box has appeared");

        } else if (primeros_bytes == SE_AGARRO_UN_OBJETO) {
            std::string mensaje = recibir_recoleccion_de_premio();

            if (mensaje.empty()) {
                mensajes.clear();
                return mensajes;
            }

            mensajes.push_back(mensaje);
        }
    }

    return mensajes;
}
