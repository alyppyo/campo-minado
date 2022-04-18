#include "TitleScreen.h"

TitleScreen::TitleScreen(sf::RenderWindow * window) : Screen::Screen(window) {
    logo_.setTexture(AssetManager::texture(Texture::Logo));
    logo_.setPosition(0, 60);

    int characterSize = 50;

    buttons_.emplace_back(L"Iniciar Jogo", characterSize);
    buttons_.emplace_back(L"Opções", characterSize);

    float height = 0.7;
    for(auto& button : buttons_) {
        centerAtPosition(button, height);
        height += 0.075;
    }
}

void TitleScreen::draw(sf::Vector2i mousePosition, MouseState mouseState) {
    Screen::draw(mousePosition, mouseState);

    window_->draw(logo_);

    for(int i = 0; i < buttons_.size(); ++i) {
        if(buttons_[i].update(mousePosition) == ButtonState::MouseHovering && mouseState == MouseState::LeftButtonPressed)
            state_ = (i == 0) ? ScreenState::ChangeToGame : ScreenState::ChangeToOptions;

        window_->draw(buttons_[i]);
    }
}
