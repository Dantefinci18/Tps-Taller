#define ARGUMENTOS_CLIENTE 3
#define NOMBRE_HOST 1
#define NOMBRE_SERVER 2

#include "client_cliente.h"
#include "common_retorno.h"

int main(int argc, const char* argv[]) {

    const char* nombre_host;
    const char* nombre_server;

    if (argc == ARGUMENTOS_CLIENTE) {
        nombre_host = argv[NOMBRE_HOST];
        nombre_server = argv[NOMBRE_SERVER];

    } else {
        return ERROR;
    }

    Cliente cliente(nombre_host, nombre_server);
    cliente.run();

    return EXITO;
}
