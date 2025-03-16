#define INDEX_BOX_ID 9
#define INDEX_N 6

#include "client_cliente.h"

#include <cctype>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "common_retorno.h"

Cliente::Cliente(const char* nombre_host, const char* nombre_servidor):
        conexion(nombre_host, nombre_servidor), protocolo(std::move(conexion)) {}

void Cliente::run() {
    std::cout << "What is your name?" << std::endl;
    std::string nombre;
    std::getline(std::cin, nombre);
    std::string comando;
    std::string numero;

    while (std::cin >> comando, comando != "Exit") {
        if (comando == "Pickup") {
            std::cin >> numero;

            if (!protocolo.recoger_caja(nombre, std::stoi(numero))) {
                break;
            }

        } else if (comando == "Read") {
            std::cin >> numero;
            std::vector<std::string> mensajes = protocolo.recibir_mensajes(std::stoi(numero));

            if (mensajes.empty()) {
                std::cerr << "Error de lectura\n";
            }

            for (size_t i = 0; i < mensajes.size(); i++) {
                std::cout << mensajes[i] << std::endl;
            }

        } else {
            std::cerr << "Accion invalida\n";
        }
    }
}
