#ifndef BUTTON_H
#define BUTTON_H

/**
 * @file Button.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Classe que representa um botão simples para interação do jogador.
 * @version 0.1
 * @date 2022-04-18
 */

// SFML
#include <SFML/Graphics.hpp>

// Projeto
#include "../System/AssetManager.h"
#include "../System/Palette.h"

/**
 * @brief Possíveis estados do botão.
 */
enum class ButtonState {
    Idle, MouseHovering
};

/**
 * @brief Classe que representa um botão simples. Sua implementação é baseada na classe Text da SFML.
 */
class Button : public sf::Text {
    ButtonState state_; //< Estado atual do botão.

public:
    Button(sf::String text, int characterSize);
    ~Button();

    ButtonState update(sf::Vector2i mousePosition);
};

#endif