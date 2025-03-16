#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <list>
#include <string>
#include <tuple>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_jugador.h"
#include "server_monitor.h"

class Aceptador: public Thread {
private:
    Socket& skt;
    std::list<Jugador*> jugadores;
    Queue<std::tuple<std::string, uint8_t>>& comandos;
    Monitor& monitor;

public:
    explicit Aceptador(Queue<std::tuple<std::string, uint8_t>>& comandos, Monitor& monitor,
                       Socket& skt);

    void cerrar_conexiones();

    void run() override;

    void eliminar_desconectados();

    std::list<Jugador*> obtener_conectados();

    void eliminar_jugador(Jugador* jugador);
};

#endif
