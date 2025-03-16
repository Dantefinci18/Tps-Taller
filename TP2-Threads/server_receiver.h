#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <mutex>
#include <string>
#include <tuple>
#include <utility>

#include "common_queue.h"
#include "common_socket.h"
#include "common_thread.h"
#include "server_protocolo.h"

class Receiver: public Thread {
private:
    Queue<std::tuple<std::string, uint8_t>>& comandos;
    ProtocoloServidor& protocolo;
    std::mutex mtx;

public:
    explicit Receiver(Queue<std::tuple<std::string, uint8_t>>& comandos,
                      ProtocoloServidor& protocolo);

    void run() override;

    bool se_cerro();
};

#endif
