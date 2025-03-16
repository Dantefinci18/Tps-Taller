#include "client_cliente.h"

#include <iostream>
#include <string>
#include <vector>

#include "common_retorno.h"

Cliente::Cliente(const char* nombre_host, const char* nombre_servidor):
        protocolo(nombre_host, nombre_servidor) {}

int Cliente::run() {
    std::vector<char> bienvenida = protocolo.recibir_mensaje();

    if (bienvenida.size() == 0) {
        return ERROR;
    }

    std::cout << bienvenida.data() << "\n";
    std::string entrada = "";

    while (true) {
        std::cin >> entrada;

        if (entrada == "q") {
            return EXITO;
        }

        if (!protocolo.enviar_orden_de_compra(entrada)) {
            return ERROR;
        }

        std::array<std::string, 3> informacion;

        if (!protocolo.recibir_informacion_de_eqipamiento(&informacion)) {
            return ERROR;
        }

        for (size_t i = 0; i < informacion.size(); i++) {
            std::cout << informacion[i] << "\n";
        }

        std::cout << "\n";
    }

    return EXITO;
}
