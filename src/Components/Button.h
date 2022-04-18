#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../System/AssetManager.h"

enum class ButtonState {
    MouseOut, MouseHovering, Pressed, Flagged
};

enum class ButtonContent {
    Empty, Text, Sprite
};

class Button : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape square_;
    ButtonState state_;
    ButtonContent content_;
    sf::Color squareOutlineColor_, squareFillColor_;
    sf::Vector2f size_;
    sf::Text text_;
    sf::Sprite sprite_;

public:
    Button();
    ~Button();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::Vector2f size();
    ButtonState state();
    void setContent(std::string text);
    void setContent(sf::Texture& texture);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setState(ButtonState state);
};

#endif