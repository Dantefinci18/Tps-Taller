#include "server_protocolo.h"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "common_rewards_ids.h"

ProtocoloServidor::ProtocoloServidor(Socket&& conexion): Protocolo(std::move(conexion)) {}

uint8_t ProtocoloServidor::recibir_box_id() {
    uint8_t box_id;
    size_t bytes_leidos = conexion.recvall(&box_id, sizeof(uint8_t), &was_closed);

    if (was_closed || bytes_leidos < sizeof(uint8_t)) {
        return 0;
    }

    return box_id;
}

uint8_t ProtocoloServidor::obtener_reward_id(const std::string& premio) {
    if (premio == "Bazooka") {
        return BAZOOKA;

    } else if (premio == "Chainsaw") {
        return CHAINSAW;

    } else if (premio == "Death ray") {
        return DEATH_RAY;

    } else if (premio == "Shotgun") {
        return SHOUTGUN;
    }

    return 0;
}

bool ProtocoloServidor::enviar_premio_recogido(const std::string& nombre,
                                               const std::string& premio) {
    uint16_t primeros_bytes = 0x0406;
    size_t bytes_enviados = conexion.sendall(&primeros_bytes, sizeof(uint16_t), &was_closed);

    if (was_closed || bytes_enviados < sizeof(uint16_t) || !enviar_nombre(nombre)) {
        return false;
    }

    uint8_t reward_id = obtener_reward_id(premio);
    bytes_enviados = conexion.sendall(&reward_id, sizeof(uint8_t), &was_closed);

    return !(was_closed || bytes_enviados < sizeof(uint8_t));
}

bool ProtocoloServidor::indicar_caja_reaparecida() {
    uint16_t reaparicion = 0x0506;
    size_t bytes_enviados = conexion.sendall(&reaparicion, sizeof(uint16_t), &was_closed);

    return !(was_closed || bytes_enviados < sizeof(uint16_t));
}

std::string ProtocoloServidor::recibir_nombre_con_el_byte() {
    uint8_t primer_byte;
    size_t bytes_leidos = conexion.recvall(&primer_byte, sizeof(uint8_t), &was_closed);

    if (was_closed || bytes_leidos < sizeof(uint8_t)) {
        return "";
    }

    return recibir_nombre();
}

void ProtocoloServidor::cerrar_conexion() {
    conexion.shutdown(2);
    conexion.close();
}
