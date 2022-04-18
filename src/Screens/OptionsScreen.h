#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../Components/Button.h"
#include "Screen.h"

#include <vector>

class OptionsScreen : public Screen {
    std::vector<sf::Text> texts_;
    std::vector<Button> buttons_;
    int& lines_;
    int& columns_;
    int& bombs_;
    int& specialists_;
    int minLines_, minColumns_, minBombs_, minSpecialists_;
    int maxLines_, maxColumns_, maxBombs_, maxSpecialists_;

public:
    OptionsScreen(sf::RenderWindow * window, int& lines, int& columns, int& bombs, int& specialists);
    ~OptionsScreen();

    virtual void draw(sf::Vector2i mousePosition, bool mousePressed = false) override;
};

#endif