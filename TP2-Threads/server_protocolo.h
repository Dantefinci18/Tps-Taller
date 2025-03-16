#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include <string>

#include "common_protocolo.h"
#include "common_rewards_ids.h"

class ProtocoloServidor: public Protocolo {
private:
    uint8_t obtener_reward_id(const std::string& premio);

public:
    explicit ProtocoloServidor(Socket&& conexion);

    uint8_t recibir_box_id();

    /*
    0x06 0x04 <player-name> <reward-id>, donde el <reward-id> es un byte con el id de la
    recompensa. Este método indica que un jugador recogió el premio de una caja.
    reward-id reward-name

        0x10  Bazooka
        0x11  Chainsaw
        0x12  Death ray
        0x13  Shotgun
    */
    bool enviar_premio_recogido(const std::string& nombre, const std::string& premio);

    /* 0x06 0x05 para indicar que una caja reapareció */
    bool indicar_caja_reaparecida();

    std::string recibir_nombre_con_el_byte();

    void cerrar_conexion();
};

#endif
