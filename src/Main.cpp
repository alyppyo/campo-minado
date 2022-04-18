/**
 * @file Main.cpp
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Ponto de partida do jogo.
 * @version 0.1
 * @date 2022-04-18
 */

// Projeto
#include "Core/GameManager.h"

/**
 * @brief Função inicial. Ponto de partida para início do jogo.
 * 
 * @return int Indica se o jogo executou adequadamente.
 */
int main() {
    // Cria o gerenciador de jogo e o executa.
    GameManager gameManager;
    gameManager.start();

    return EXIT_SUCCESS;
}
