#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>

#include "../Screens/GameScreen.h"
#include "../Screens/GameOverScreen.h"
#include "../Screens/TitleScreen.h"

class GameManager {
    sf::RenderWindow window_;
    std::unique_ptr<Screen> currentScreen_;

public:
    GameManager();
    ~GameManager();

    void checkScreenStatus();
    void loop();
    void start();
};

#endif