#define BAZOOKA 1
#define CHAINSAW 2
#define DEATH_RAY 3
#define SHOTGUN 4

#include "server_cajas_recompensa.h"

#include <stdexcept>

#include "server_ejecutado.h"

std::string CajasRecompensa::recojer_premio(uint8_t box_id) {
    if (!cajas[box_id - 1]) {
        return "";
    }

    std::string premio;

    switch (box_id) {
        case BAZOOKA:
            premio = "Bazooka";
            bazooka_loops = 0;
            break;

        case CHAINSAW:
            premio = "Chainsaw";
            chainsaw_loops = 0;
            break;

        case DEATH_RAY:
            premio = "Death ray";
            death_ray_loops = 0;
            break;

        case SHOTGUN:
            premio = "Shotgun";
            shotgun_loops = 0;
            break;

        default:
            throw std::runtime_error("Box Id incorrecto");
    }

    cajas[box_id - 1] = false;

    return premio;
}

void CajasRecompensa::restablecer_premios(Monitor& monitor) {
    ejecutado ejecutado;

    if (!cajas[BAZOOKA - 1]) {
        if (bazooka_loops == ITERACIONES_BAZOOKA) {
            cajas[BAZOOKA - 1] = true;
            ejecutado.nuevo_aparecido = true;
            monitor.enviar_ejecutado(ejecutado);

        } else {
            bazooka_loops++;
        }
    }

    if (!cajas[CHAINSAW - 1]) {

        if (chainsaw_loops == ITERACIONES_CHAINSAW) {
            cajas[CHAINSAW - 1] = true;
            ejecutado.nuevo_aparecido = true;
            monitor.enviar_ejecutado(ejecutado);

        } else {
            chainsaw_loops++;
        }
    }

    if (!cajas[DEATH_RAY - 1]) {
        if (death_ray_loops == ITERACIONES_DEATH_RAY) {
            cajas[DEATH_RAY - 1] = true;
            ejecutado.nuevo_aparecido = true;
            monitor.enviar_ejecutado(ejecutado);

        } else {
            death_ray_loops++;
        }
    }

    if (!cajas[SHOTGUN - 1]) {
        if (shotgun_loops == ITERACIONES_SHOTGUN) {
            cajas[SHOTGUN - 1] = true;
            ejecutado.nuevo_aparecido = true;
            monitor.enviar_ejecutado(ejecutado);

        } else {
            shotgun_loops++;
        }
    }
}
