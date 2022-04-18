#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "../System/AssetManager.h"
#include "../System/Palette.h"

enum class ScreenStatus {
    Idle, ChangeToTitle, ChangeToGame, ChangeToGameOverVictory, ChangeToGameOverDefeat
};

class Screen {
protected:    
    sf::RenderWindow * window_;
    ScreenStatus status_;

public:
    Screen(sf::RenderWindow * window);
    virtual void draw(sf::Vector2i mousePosition, bool mousePressed);
    ScreenStatus status();
    void setStatus(ScreenStatus status);
};

#endif
