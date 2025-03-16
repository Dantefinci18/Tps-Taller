#define NOMBRE 0
#define BOX_ID 1
#define TIMER_SLEEP 200
#define ID_BAZOPKA 1
#define ID_CHAINSAW 2
#define ID_DEATH_RAY 3
#define ID_SHOTGUN 4

#include "server_gameloop.h"

#include "server_ejecutado.h"

Gameloop::Gameloop(Queue<std::tuple<std::string, uint8_t>>& comandos, Monitor& monitor):
        clients_commands(comandos), monitor(monitor) {}

void Gameloop::ejecutar_comandos() {
    std::lock_guard<std::mutex> lock(mtx);
    std::tuple<std::string, uint8_t> comando;

    while (clients_commands.try_pop(comando)) {
        ejecutado ejecutado;
        ejecutado.nombre = std::get<NOMBRE>(comando);
        uint8_t box_id = std::get<BOX_ID>(comando);

        if ((ejecutado.premio = juego.recojer_premio(box_id)) != "") {
            monitor.enviar_ejecutado(ejecutado);
        }
    }
}


void Gameloop::run() {
    while (_keep_running) {
        ejecutar_comandos();
        mtx.lock();
        juego.restablecer_premios(monitor);
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_SLEEP));
    }
}
