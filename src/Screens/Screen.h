#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "../Components/Button.h"
#include "../System/AssetManager.h"
#include "../System/Palette.h"

enum class ScreenState {
    Idle, ChangeToTitle, ChangeToOptions, ChangeToGame, ChangeToGameOverVictory, ChangeToGameOverDefeat
};

enum class MouseState {
    Idle, LeftButtonPressed, RightButtonPressed, MiddleButtonPressed
};

class Screen {
protected:    
    sf::RenderWindow * window_;
    ScreenState state_;

public:
    Screen(sf::RenderWindow * window);
    void centerAtPosition(sf::Text& text, float height);
    void resize(int width, int height);
    ScreenState state();
    void setState(ScreenState state);
    
    virtual void draw(sf::Vector2i mousePosition, MouseState mouseState);
};

#endif
