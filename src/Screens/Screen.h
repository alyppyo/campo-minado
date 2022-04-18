#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "../System/AssetManager.h"

enum class ScreenType {
    Title, Game, Options, Credits, GameOver
};

class Screen {
protected:    
    sf::RenderWindow * window_;
    sf::Color backgroundColor_;

public:
    Screen();
    virtual void draw();
    virtual void initComponents(sf::RenderWindow * window);
};

#endif
