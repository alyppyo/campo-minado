/**
 * @file GameOverScreen.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Tela de finalização do jogo.
 * @version 0.1
 * @date 2022-04-18
 */

#ifndef GAME_OVER_SCREEN
#define GAME_OVER_SCREEN

// Projeto
#include "Screen.h"
#include "../Components/Button.h"

/**
 * @brief Tela de finalização do jogo.
 */
class GameOverScreen : public Screen {
    sf::Text mainMessage_;
    sf::Text supportMessage_;
    Button returnButton_;

public:
    GameOverScreen(sf::RenderWindow * window, bool victory);
    ~GameOverScreen();
    
    virtual void draw(sf::Vector2i mousePosition, MouseState mouseState) override;
};

#endif