#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "Screen.h"

class TitleScreen : public Screen {
    sf::Sprite logo_;

public:
    TitleScreen(sf::RenderWindow * window);
    virtual void draw();
};

#endif