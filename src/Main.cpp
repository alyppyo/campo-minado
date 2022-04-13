#include <cstdlib>
#include <iostream>
#include <string>

#include "CampoMinado.h"

int main(int argc, char ** argv) {
    CampoMinado jogo(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    jogo.iniciar();

    return EXIT_SUCCESS;
}