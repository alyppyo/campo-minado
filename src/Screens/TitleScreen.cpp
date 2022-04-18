#include "TitleScreen.h"

TitleScreen::TitleScreen(sf::RenderWindow * window) : Screen::Screen(window) {
    logo_.setTexture(AssetManager::texture(Texture::Logo));

    // Centralizar mensagem.
    // sf::FloatRect bounds = logo_.getLocalBounds();
    // logo_.setOrigin(bounds.left + bounds.width/2,
    //                 bounds.top + bounds.height/2);
    //logo_.setPosition(window_->getSize().x*0.5, window_->getSize().y*0.4);

    std::cout << logo_.getPosition().x << " " << logo_.getPosition().y << std::endl;
}

void TitleScreen::draw() {
    window_->draw(logo_);
}
