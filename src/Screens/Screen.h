#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "../Components/Button.h"
#include "../System/AssetManager.h"
#include "../System/Palette.h"

enum class ScreenStatus {
    Idle, ChangeToTitle, ChangeToOptions, ChangeToGame, ChangeToGameOverVictory, ChangeToGameOverDefeat
};

class Screen {
protected:    
    sf::RenderWindow * window_;
    ScreenStatus status_;

public:
    Screen(sf::RenderWindow * window);
    void centerAtPosition(sf::Text& text, float height);
    virtual void draw(sf::Vector2i mousePosition, bool mousePressed);
    void resize(int width, int height);
    ScreenStatus status();
    void setStatus(ScreenStatus status);
};

#endif
