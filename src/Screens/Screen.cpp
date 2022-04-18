#include "Screen.h"

Screen::Screen() : backgroundColor_(sf::Color::White) {}

void Screen::init(sf::RenderWindow * window) {
    window_ = window;
}

void Screen::draw() {
    window_->clear(backgroundColor_);
}
