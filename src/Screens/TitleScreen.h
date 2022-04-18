#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

/**
 * @file TitleScreen.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Classe que representa a tela inicial do Campo Minado.
 * @version 0.1
 * @date 2022-04-18
 */

// C++
#include <list>

// Projeto
#include "Screen.h"
#include "../Components/Button.h"

/**
 * @brief Classe que representa a tela inicial do Campo Minado.
 */
class TitleScreen : public Screen {
    sf::Sprite logo_;
    std::vector<Button> buttons_;

public:
    TitleScreen(sf::RenderWindow * window);
    virtual void draw(sf::Vector2i mousePosition, MouseState mouseState) override;
};

#endif