#include "server_sender.h"

#include <string>

Sender::Sender(ProtocoloServidor& protocolo, Monitor& monitor):
        protocolo(protocolo), monitor(monitor) {}

void Sender::enviar_ejecutados() {
    while (_keep_running) {
        ejecutado ejecutado = server_msg.pop();

        if (ejecutado.nuevo_aparecido) {

            if (!protocolo.indicar_caja_reaparecida())
                _keep_running = false;

        } else {
            if (!protocolo.enviar_premio_recogido(ejecutado.nombre, ejecutado.premio))
                _keep_running = false;
        }
    }
}


void Sender::stop() {
    _keep_running = false;
    server_msg.close();
}

void Sender::run() {
    monitor.agregar_queue(server_msg);

    try {
        enviar_ejecutados();

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error de escritura: " << e.what() << "\n";
    }

    monitor.eliminar_queue(server_msg);
}

bool Sender::se_cerro() { return !_keep_running; }
