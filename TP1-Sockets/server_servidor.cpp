#include "server_servidor.h"

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "common_retorno.h"

Servidor::Servidor(const char* nombre_servidor): protocolo(nombre_servidor) {}

int Servidor::run() {
    const char* pregunta_inicial = "What arya buying?";
    uint16_t bytes_a_enviar = strlen(pregunta_inicial);

    if (!protocolo.enviar_mensaje(bytes_a_enviar, pregunta_inicial)) {
        return ERROR;
    }

    std::vector<std::string> operaciones;
    int se_realizo_la_orden;

    while ((se_realizo_la_orden = protocolo.realizar_orden_de_compra(&operaciones)) !=
           CONEXION_CERRADA) {

        if (se_realizo_la_orden == ERROR) {
            return ERROR;
        }

        for (size_t i = 0; i < operaciones.size(); i++) {
            std::cout << operaciones[i] << "\n";
        }

        operaciones.clear();
        protocolo.enviar_equipamiento();
    }

    return EXITO;
}
