#define BANANA 1
#define MAGNUM 2
#define OLD_PISTOL 3
#define PEW_PEW_LASER 4
#define PHASER 5
#define CHAINDART 6
#define MUNICION_SEGUNDA_ARMA 7
#define MUNICION_PRIMERA_ARMA 8
#define CUCHILLO 9
#define AUMENTO_SEGUNDA_MUNICION 7
#define AUMENTO_PRIMERA_MUNICION 10

#include "common_duckgame.h"

#include <cstring>

DuckGame::DuckGame(): arma_1(""), municion_1(0), arma_2(""), municion_2(0), cuchillo(false) {}

std::string DuckGame::puntero_char_de_municion(const std::string& equipamento, int municion) {
    std::string str_municion = std::to_string(municion);
    std::string str_resultado = equipamento + str_municion;
    return str_resultado;
}


std::string DuckGame::agregar_equipamento(uint8_t num) {

    switch (num) {
        case BANANA:
            arma_2 = "Banana";
            municion_2 = 0;
            return arma_2;

        case MAGNUM:
            arma_2 = "Magnum";
            municion_2 = 0;
            return arma_2;

        case OLD_PISTOL:
            arma_2 = "Old Pistol";
            municion_2 = 0;
            return arma_2;

        case PEW_PEW_LASER:
            arma_1 = "Pew Pew Laser";
            municion_1 = 0;
            return arma_1;

        case PHASER:
            arma_1 = "Phaser";
            municion_1 = 0;
            return arma_1;

        case CHAINDART:
            arma_1 = "Chaindart";
            municion_1 = 0;
            return arma_1;

        case MUNICION_SEGUNDA_ARMA:
            if (strcmp(arma_2.data(), "") != 0) {
                municion_2 += AUMENTO_SEGUNDA_MUNICION;
            }

            return puntero_char_de_municion("Secondary Ammo: ", municion_2);

        case MUNICION_PRIMERA_ARMA:
            if (strcmp(arma_1.data(), "") != 0) {
                municion_1 += AUMENTO_PRIMERA_MUNICION;
            }

            return puntero_char_de_municion("Primary Ammo: ", municion_1);

        case CUCHILLO:
            cuchillo = !cuchillo;

            if (cuchillo) {
                return "Equipped knife";
            }

            return "Knife not equipped";
    }

    return "";
}

const char* DuckGame::get_primer_arma() { return arma_1.c_str(); }

const char* DuckGame::get_segunda_arma() { return arma_2.c_str(); }

uint8_t DuckGame::get_municion_primera_arma() { return municion_1; }

uint8_t DuckGame::get_municion_segunda_arma() { return municion_2; }

uint8_t DuckGame::cuchillo_equipado() {
    if (cuchillo) {
        return CUCHILLO_EQUIPADO;
    }

    return CUCHILLO_DESEQUIPADO;
}
