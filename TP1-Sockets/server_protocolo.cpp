#define CODIGO_PRODUCTO_CHAR 1
#define CODIGO_PRODUCTO_STRING 2

#include "server_protocolo.h"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>

#include "common_retorno.h"

ProtocoloServidor::ProtocoloServidor(const char* nombre_servidor):
        skt_servidor(nombre_servidor),
        conexion_cliente(skt_servidor.accept()),
        duckgame(DuckGame()) {}

bool ProtocoloServidor::enviar_mensaje(const uint16_t sz, const char* mensaje) {
    bool was_closed = false;
    uint16_t sz_big_endian = htons(sz);
    conexion_cliente.sendall(&sz_big_endian, sizeof(uint16_t), &was_closed);

    if (was_closed) {
        return false;
    }

    int bytes_enviados = conexion_cliente.sendall(mensaje, sz, &was_closed);
    return !(was_closed || bytes_enviados < sz);
}

int ProtocoloServidor::realizar_orden_de_compra(std::vector<std::string>* operaciones) {

    char buffer[CODIGO_PRODUCTO_STRING];
    int buffer_sz = CODIGO_PRODUCTO_CHAR;
    bool was_closed = false;
    // recibo la primer letra y verifico si es la 'B'
    int bytes_leidos = conexion_cliente.recvall(buffer, buffer_sz, &was_closed);

    if (was_closed) {
        return CONEXION_CERRADA;
    }


    if (bytes_leidos < buffer_sz || buffer[0] != 'B') {
        return ERROR;
    }

    while (true) {
        bytes_leidos = conexion_cliente.recvall(buffer, buffer_sz, &was_closed);

        if (was_closed) {
            return CONEXION_CERRADA;
        }

        if (buffer[0] == '\0') {
            return EXITO;
        }

        if (bytes_leidos < buffer_sz || !std::isdigit(buffer[0])) {
            return ERROR;
        }

        buffer[CODIGO_PRODUCTO_CHAR] = '\0';

        std::string operacion = duckgame.agregar_equipamento(std::atoi(buffer));
        (*operaciones).push_back(operacion);
    }

    return EXITO;
}

bool ProtocoloServidor::enviar_arma(const char* arma) {
    if (strcmp(arma, "") == 0) {
        const char* mensaje = "Not Equipped";
        return enviar_mensaje(strlen(mensaje), mensaje);
    }

    return enviar_mensaje(strlen(arma), arma);
}

bool ProtocoloServidor::enviar_numero(uint8_t num) {
    bool was_closed = false;
    uint8_t sz = sizeof(num);
    int bytes_enviados = conexion_cliente.sendall(&num, sz, &was_closed);
    return !(was_closed || bytes_enviados < sz);
}

bool ProtocoloServidor::enviar_equipamiento() {
    const char* arma_1 = duckgame.get_primer_arma();

    if (!enviar_arma(arma_1)) {
        return false;
    }

    uint8_t municion_1 = duckgame.get_municion_primera_arma();

    if (!enviar_numero(municion_1)) {
        return false;
    }

    const char* arma_2 = duckgame.get_segunda_arma();

    if (!enviar_arma(arma_2)) {
        return false;
    }

    uint8_t municion_2 = duckgame.get_municion_segunda_arma();

    if (!enviar_numero(municion_2)) {
        return false;
    }

    uint8_t hay_cuchillo = duckgame.cuchillo_equipado();
    bool se_envio_cuchillo = enviar_numero(hay_cuchillo);
    return se_envio_cuchillo;
}
