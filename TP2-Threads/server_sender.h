#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <mutex>
#include <string>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_ejecutado.h"
#include "server_monitor.h"
#include "server_protocolo.h"

class Sender: public Thread {
private:
    ProtocoloServidor& protocolo;
    Queue<ejecutado> server_msg;
    Monitor& monitor;
    std::mutex mtx;

    void enviar_ejecutados();

public:
    explicit Sender(ProtocoloServidor& protocolo, Monitor& monitor);

    void stop() override;

    void run() override;

    bool se_cerro();
};

#endif
