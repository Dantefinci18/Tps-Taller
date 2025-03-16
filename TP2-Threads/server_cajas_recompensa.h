#ifndef SERVER_CAJAS_RECOMPENSA_H
#define SERVER_CAJAS_RECOMPENSA_H

#define ITERACIONES_BAZOOKA 15
#define ITERACIONES_CHAINSAW 5
#define ITERACIONES_DEATH_RAY 20
#define ITERACIONES_SHOTGUN 10

#include <cstdint>
#include <list>
#include <string>
#include <vector>

#include "server_monitor.h"

class CajasRecompensa {
private:
    std::vector<bool> cajas = {true, true, true, true};
    int bazooka_loops = ITERACIONES_BAZOOKA;
    int chainsaw_loops = ITERACIONES_CHAINSAW;
    int death_ray_loops = ITERACIONES_DEATH_RAY;
    int shotgun_loops = ITERACIONES_SHOTGUN;

public:
    std::string recojer_premio(uint8_t box_id);
    void restablecer_premios(Monitor& monitor);
};

#endif
