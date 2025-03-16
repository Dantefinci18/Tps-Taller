#ifndef SERVER_JUGADOR_H
#define SERVER_JUGADOR_H

#include <string>
#include <tuple>

#include "common_socket.h"
#include "server_monitor.h"
#include "server_receiver.h"
#include "server_sender.h"

class Jugador {
private:
    ProtocoloServidor protocolo;
    Sender sender;
    Receiver receiver;

public:
    explicit Jugador(Queue<std::tuple<std::string, uint8_t>>& comandos, Monitor& monitor,
                     Socket&& conexion);

    void run();

    void stop();

    bool esta_conectado();

    void cerrar_conexion();
};

#endif
