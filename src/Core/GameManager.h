#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

/**
 * @file GameManager.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Classe que representa o gerenciador de jogos.
 * @version 0.1
 * @date 2022-04-18
 */

// SFML
#include <SFML/Graphics.hpp>

// Projeto
#include "../Screens/TitleScreen.h"
#include "../Screens/OptionsScreen.h"
#include "../Screens/GameScreen.h"
#include "../Screens/GameOverScreen.h"

/**
 * @brief Classe que representa o gerenciador de jogos.
 */
class GameManager {
    int screenWidth_, screenHeight_;
    sf::RenderWindow window_;
    std::unique_ptr<Screen> currentScreen_;
    int lines_, columns_, bombs_, specialists_;

public:
    GameManager();
    ~GameManager();

    void checkScreenStatus();
    void loop();
    void start();
};

#endif