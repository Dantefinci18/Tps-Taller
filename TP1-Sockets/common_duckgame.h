#ifndef COMMON_DUCKGAME_H
#define COMNON_DUCKGAME_H

#define CUCHILLO_EQUIPADO 1
#define CUCHILLO_DESEQUIPADO 0

#include <map>
#include <string>

#include <stdint.h>

class DuckGame {
private:
    std::string arma_1;
    int municion_1;
    std::string arma_2;
    int municion_2;
    bool cuchillo;

    std::string puntero_char_de_municion(const std::string& equipamento, int municion);

public:
    DuckGame();

    /*
    Devuelve una cadena con el equipamiento establecido.
    Si el num es incorrecto devuelve una cadena vacia
    */
    std::string agregar_equipamento(uint8_t num);

    const char* get_primer_arma();

    const char* get_segunda_arma();

    uint8_t get_municion_primera_arma();

    uint8_t get_municion_segunda_arma();

    uint8_t cuchillo_equipado();
};

#endif
