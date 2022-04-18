#include "Screen.h"

Screen::Screen(sf::RenderWindow * window) : window_(window), status_(ScreenStatus::Idle) {}

void Screen::centerAtPosition(sf::Text& text, float height) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(bounds.left + bounds.width/2, bounds.top + bounds.height/2));
    text.setPosition(sf::Vector2f(window_->getSize().x*0.5, window_->getSize().y*height));
}

void Screen::draw(sf::Vector2i mousePosition, bool mousePressed) {
    window_->clear(Palette::Background);
}

void Screen::resize(int width, int height) {
    window_->setSize(sf::Vector2u(width, height));
    window_->setView(sf::View(sf::FloatRect(0, 0, width, height)));
}

ScreenStatus Screen::status() {
    return status_;
}

void Screen::setStatus(ScreenStatus status) {
    status_ = status;
}

