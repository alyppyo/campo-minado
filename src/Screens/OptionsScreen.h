#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H

/**
 * @file OptionsScreen.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Tela de opções do jogo.
 * @version 0.1
 * @date 2022-04-18
 */

// C++
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// Projeto
#include "../Components/Button.h"
#include "Screen.h"

/**
 * @brief Tela de opções do jogo.
 */
class OptionsScreen : public Screen {
    std::vector<sf::Text> texts_;
    std::vector<Button> buttons_;
    int& lines_;
    int& columns_;
    int& bombs_;
    int& specialists_;
    int minLines_, minColumns_, minBombs_, minSpecialists_;
    int maxLines_, maxColumns_, maxBombs_, maxSpecialists_;

public:
    OptionsScreen(sf::RenderWindow * window, int& lines, int& columns, int& bombs, int& specialists);
    ~OptionsScreen();

    virtual void draw(sf::Vector2i mousePosition, MouseState mouseState) override;
};

#endif
