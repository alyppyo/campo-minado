#include "Button.h"

Button::Button(sf::String text, int characterSize) : state_(ButtonState::Idle) {
    setFont(AssetManager::font(Font::MotionControl));
    setString(text);
    setCharacterSize(characterSize);
    setFillColor(Palette::Text);
}

Button::~Button() {}

ButtonState Button::update(sf::Vector2i mousePosition) {
    if(state_ == ButtonState::Idle && getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
        state_ = ButtonState::MouseHovering;
        setFillColor(Palette::ButtonSelected);
    }
    else if(state_ == ButtonState::MouseHovering && !getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))) { 
        state_ = ButtonState::Idle;
        setFillColor(Palette::Text);
    }

    return state_;
}


