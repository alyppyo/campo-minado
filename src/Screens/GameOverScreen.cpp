#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(sf::RenderWindow * window, bool victory) : Screen::Screen(window) {
    // Mensagem principal.
    mainMessage_.setFont(AssetManager::font(Font::MotionControl));
    mainMessage_.setCharacterSize(80);
    mainMessage_.setString(victory ? sf::String(L"Você venceu!") : sf::String(L"Você explodiu..."));

    // Centralizar mensagem.
    sf::FloatRect bounds = mainMessage_.getLocalBounds();
    mainMessage_.setOrigin(bounds.left + bounds.width/2,
                           bounds.top + bounds.height/2);
    mainMessage_.setPosition(window_->getSize().x*0.5, window_->getSize().y*0.4);

    // Mensagem de suporte.
    supportMessage_.setFont(AssetManager::font(Font::Roboto));
    supportMessage_.setCharacterSize(24);
    supportMessage_.setString(victory ?
                              sf::String(L"Parabéns! Conseguiu desviar de todas as bombas!") :
                              sf::String(L"Sugerimos que procure o hospital mais próximo."));
    
    // Centralizar mensagem.
    bounds = supportMessage_.getLocalBounds();
    supportMessage_.setOrigin(bounds.left + bounds.width/2,
                              bounds.top  + bounds.height/2);
    supportMessage_.setPosition(window_->getSize().x*0.5, window_->getSize().y*0.5);
}

GameOverScreen::~GameOverScreen() {}

void GameOverScreen::draw(sf::Vector2i mousePosition, bool mousePressed) {
    Screen::draw(mousePosition, mousePressed);

    window_->draw(mainMessage_);
    window_->draw(supportMessage_);
}
