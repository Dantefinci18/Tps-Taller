#include "server_receiver.h"

#include <sstream>
#include <string>

Receiver::Receiver(Queue<std::tuple<std::string, uint8_t>>& comandos, ProtocoloServidor& protocolo):
        comandos(comandos), protocolo(protocolo) {}

void Receiver::run() {
    try {
        while (_keep_running) {
            std::string nombre = protocolo.recibir_nombre_con_el_byte();
            uint8_t box_id = protocolo.recibir_box_id();

            if (box_id == 0 || nombre == "") {
                _keep_running = false;
                continue;
            }

            std::tuple<std::string, uint8_t> comando(nombre, box_id);
            std::lock_guard<std::mutex> lock(mtx);
            comandos.push(comando);
        }

    } catch (std::exception& e) {
        if (_keep_running)
            std::cerr << "Error: " << e.what() << "\n";
    }
}

bool Receiver::se_cerro() { return !_keep_running; }
