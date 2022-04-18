#include "Screen.h"

Screen::Screen(sf::RenderWindow * window) : window_(window) {}

void Screen::draw(sf::Vector2i mousePosition, bool mousePressed) {
    window_->clear(Palette::Background);
}

ScreenStatus Screen::status() {
    return status_;
}

void Screen::setStatus(ScreenStatus status) {
    status_ = status;
}