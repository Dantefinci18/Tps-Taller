#include "common_protocolo.h"

#include <utility>

#include <arpa/inet.h>

Protocolo::Protocolo(Socket&& conexion): conexion(std::move(conexion)) {}

std::string Protocolo::recibir_nombre() {
    uint16_t largo_nombre_be;
    size_t bytes_leidos = conexion.recvall(&largo_nombre_be, sizeof(uint16_t), &was_closed);
    uint16_t largo_nombre = ntohs(largo_nombre_be);

    if (was_closed || bytes_leidos < sizeof(uint16_t)) {
        return "";
    }

    std::string nombre;
    nombre.resize(largo_nombre);
    bytes_leidos = conexion.recvall(nombre.data(), largo_nombre, &was_closed);

    if (was_closed || bytes_leidos < largo_nombre) {
        return "";
    }

    return nombre;
}

bool Protocolo::enviar_nombre(const std::string& nombre) {
    uint16_t largo_nombre = htons(nombre.size());
    size_t bytes_enviados = conexion.sendall(&largo_nombre, sizeof(uint16_t), &was_closed);

    if (was_closed || bytes_enviados < sizeof(uint16_t))
        return false;

    bytes_enviados = conexion.sendall(nombre.data(), nombre.size(), &was_closed);

    return !(was_closed || bytes_enviados < nombre.size());
}
