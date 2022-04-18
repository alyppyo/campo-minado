#ifndef GAME_OVER_SCREEN
#define GAME_OVER_SCREEN

#include "Screen.h"
#include "../Components/Button.h"

class GameOverScreen : public Screen {
    sf::Text mainMessage_;
    sf::Text supportMessage_;
    Button returnButton_;

public:
    GameOverScreen();
    ~GameOverScreen() = default;
    
    void draw(sf::Vector2i mousePosition, bool mousePressed = false);
    void init();
};

#endif