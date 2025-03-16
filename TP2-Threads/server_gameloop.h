#ifndef SERVER_GAMELOOP_H
#define SERVER_GAMELOOP_H

#include <list>
#include <mutex>
#include <string>
#include <tuple>

#include "common_queue.h"
#include "common_thread.h"
#include "server_cajas_recompensa.h"
#include "server_monitor.h"

class Gameloop: public Thread {
private:
    Queue<std::tuple<std::string, uint8_t>>& clients_commands;
    CajasRecompensa juego;
    Monitor& monitor;
    std::mutex mtx;

    void ejecutar_comandos();

public:
    explicit Gameloop(Queue<std::tuple<std::string, uint8_t>>& comandos, Monitor& monitor);

    void run() override;
};

#endif
