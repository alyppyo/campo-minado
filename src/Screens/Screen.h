#ifndef SCREEN_H
#define SCREEN_H

/**
 * @file Screen.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Tela base para todas as demais do jogo.
 * @version 0.1
 * @date 2022-04-18
 */

// SFML
#include <SFML/Graphics.hpp>

// Projeto
#include "../Components/Button.h"
#include "../System/AssetManager.h"
#include "../System/Palette.h"

/**
 * @brief Estados possíveis para uma tela.
 */
enum class ScreenState {
    Idle, ChangeToTitle, ChangeToOptions, ChangeToGame, ChangeToGameOverVictory, ChangeToGameOverDefeat
};

/**
 * @brief Estados possíveis para o mouse.
 */
enum class MouseState {
    Idle, LeftButtonPressed, RightButtonPressed, MiddleButtonPressed
};

/**
 * @brief Tela base para todas as demais telas do jogo.
 */
class Screen {
protected:    
    sf::RenderWindow * window_;
    ScreenState state_;

public:
    Screen(sf::RenderWindow * window);
    void centerAtPosition(sf::Text& text, float height);
    void resize(int width, int height);
    ScreenState state();
    void setState(ScreenState state);
    
    virtual void draw(sf::Vector2i mousePosition, MouseState mouseState);
};

#endif
