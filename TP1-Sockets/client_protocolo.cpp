#define MAYOR_TAMANIO_STRRING_ARMA 30
#define TAMANIO_STRING_OPERACION 100
#define CUCHILLO 2
#define CANTIDAD_DE_ARMAS 2
#define FINAL_STRING 1

#include "client_protocolo.h"

#include <cstdio>
#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "common_retorno.h"


ProtocoloCliente::ProtocoloCliente(const char* nombre_host, const char* nombre_servidor):
        skt_cliente(nombre_host, nombre_servidor) {}

std::vector<char> ProtocoloCliente::recibir_mensaje() {

    uint16_t sz_big_endian;
    bool was_closed = false;
    skt_cliente.recvall(&sz_big_endian, sizeof(uint16_t), &was_closed);

    if (was_closed) {
        return std::vector<char>(0);
    }

    uint16_t sz = ntohs(sz_big_endian);
    std::vector<char> buffer(sz + FINAL_STRING);
    int bytes_leidos = skt_cliente.recvall(buffer.data(), sz, &was_closed);

    if (was_closed || bytes_leidos < sz) {
        return std::vector<char>(0);
    }

    buffer[sz] = '\0';
    return buffer;
}

bool ProtocoloCliente::enviar_orden_de_compra(const std::string& orden_de_compra) {
    bool was_closed = false;
    std::vector<char> vec_orden_de_compra(orden_de_compra.begin(), orden_de_compra.end());
    vec_orden_de_compra.push_back('\0');
    size_t bytes_enviados = skt_cliente.sendall(vec_orden_de_compra.data(),
                                                vec_orden_de_compra.size(), &was_closed);

    return !(was_closed || bytes_enviados < vec_orden_de_compra.size());
}

bool ProtocoloCliente::recibir_numero(uint8_t* num) {
    bool was_closed = false;
    uint8_t sz = sizeof(*num);
    int bytes_leidos = skt_cliente.recvall(num, sz, &was_closed);
    return !(was_closed || bytes_leidos < sz);
}

bool ProtocoloCliente::recibir_informacion_de_eqipamiento(std::array<std::string, 3>* informacion) {
    const char* armas[CANTIDAD_DE_ARMAS] = {"Primary Weapon: ", "Secondary Weapon: "};

    for (int i = 0; i < CUCHILLO; i++) {
        uint8_t num;

        std::vector<char> arma = recibir_mensaje();

        if (arma.size() == 0 || !recibir_numero(&num)) {
            return false;
        }

        (*informacion)[i] = std::string(armas[i]) + std::string(arma.data()) +
                            std::string(" | Ammo: ") + std::to_string(num);
    }

    uint8_t num;
    if (!recibir_numero(&num)) {
        return false;
    }

    if (num == 0) {
        (*informacion)[CUCHILLO] = "Knife Equipped: No";

    } else {
        (*informacion)[CUCHILLO] = "Knife Equipped: Yes";
    }

    return true;
}
