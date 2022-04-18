/**
 * @file Button.cpp
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Implementação dos métodos da classe "Button", botão simples para interação.
 * @version 0.1
 * @date 2022-04-18
 */

#include "Button.h"

/**
 * @brief Constrói um novo botão.
 * 
 * @param text Texto do botão.
 * @param characterSize Tamanho dos caracteres do texto do botão.
 */
Button::Button(sf::String text, int characterSize) : state_(ButtonState::Idle) {
    setFont(AssetManager::font(Font::MotionControl));
    setString(text);
    setCharacterSize(characterSize);
    setFillColor(Palette::Text);
}

/**
 * @brief Destrutor padrão.
 */
Button::~Button() {}

/**
 * @brief Atualiza o botão de acordo com a posição do mouse no momento.
 * 
 * @param mousePosition Posição do mouse.
 * @return ButtonState O novo estado do botão.
 */
ButtonState Button::update(sf::Vector2i mousePosition) {
    // Caso o botão esteja ocioso e o mouse esteja dentro de seus limites,
    // seu estado será "MouseHovering".
    if(state_ == ButtonState::Idle && getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        state_ = ButtonState::MouseHovering;
        setFillColor(Palette::ButtonSelected);
    }
    // Caso o estado atual indique que o mouse está em cima, mas a posição indica o contrário,
    // seu estado retornará ao ocioso.
    else if(state_ == ButtonState::MouseHovering && !getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) { 
        state_ = ButtonState::Idle;
        setFillColor(Palette::Text);
    }

    // Retorna o estado atual do botão.
    return state_;
}


