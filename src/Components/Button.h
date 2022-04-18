#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "../System/AssetManager.h"
#include "../System/Palette.h"

#include <iostream>

enum class ButtonState {
    Idle, MouseHovering
};

class Button : public sf::Text {
    ButtonState state_;

public:
    Button(sf::String text, int characterSize);
    ~Button();

    ButtonState update(sf::Vector2i mousePosition);
};

#endif