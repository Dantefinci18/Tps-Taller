#include "server_monitor.h"

#include <iostream>
#include <string>

void Monitor::agregar_queue(Queue<ejecutado>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    queues_de_ejecutados.push_back(&queue);
}

void Monitor::eliminar_queue(Queue<ejecutado>& queue) {
    std::lock_guard<std::mutex> lock(mtx);
    queues_de_ejecutados.remove(&queue);
}

void Monitor::enviar_ejecutado(const ejecutado& ejecutado) {
    if (ejecutado.nuevo_aparecido) {
        std::cout << "A new box has appeared\n";

    } else {
        std::cout << ejecutado.nombre + " picked up a " + ejecutado.premio << "\n";
    }

    for (auto queue: queues_de_ejecutados) {

        queue->push(ejecutado);
    }
}
