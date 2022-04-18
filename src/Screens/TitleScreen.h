#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "Screen.h"
#include "../Components/Button.h"

#include <list>

class TitleScreen : public Screen {
    sf::Sprite logo_;
    std::vector<Button> buttons_;

public:
    TitleScreen(sf::RenderWindow * window);
    virtual void draw(sf::Vector2i mousePosition, MouseState mouseState) override;
};

#endif