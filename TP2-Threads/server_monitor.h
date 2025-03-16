#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <list>
#include <mutex>
#include <string>

#include "common_queue.h"
#include "server_ejecutado.h"

class Monitor {
private:
    std::list<Queue<ejecutado>*> queues_de_ejecutados;
    std::mutex mtx;

public:
    void agregar_queue(Queue<ejecutado>& queue);

    void eliminar_queue(Queue<ejecutado>& queue);

    void enviar_ejecutado(const ejecutado& ejecutado);
};

#endif
