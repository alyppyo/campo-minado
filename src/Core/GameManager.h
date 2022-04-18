#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>

#include "../Screens/TitleScreen.h"
#include "../Screens/OptionsScreen.h"
#include "../Screens/GameScreen.h"
#include "../Screens/GameOverScreen.h"

class GameManager {
    int screenWidth_, screenHeight_;
    sf::RenderWindow window_;
    std::unique_ptr<Screen> currentScreen_;
    int lines_, columns_, bombs_, specialists_;

public:
    GameManager();
    ~GameManager();

    void checkScreenStatus();
    void loop();
    void start();
};

#endif