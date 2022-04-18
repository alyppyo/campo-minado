#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(sf::RenderWindow * window, bool victory) :
    Screen::Screen(window), returnButton_(L"Voltar para a tela inicial", 50) {
    // Mensagem principal.
    mainMessage_.setFont(AssetManager::font(Font::MotionControl));
    mainMessage_.setCharacterSize(80);
    mainMessage_.setString(victory ? sf::String(L"Você venceu!") : sf::String(L"Você explodiu..."));
    centerAtPosition(mainMessage_, 0.4);

    // Mensagem de suporte.
    supportMessage_.setFont(AssetManager::font(Font::Roboto));
    supportMessage_.setCharacterSize(24);
    supportMessage_.setString(victory ?
                              sf::String(L"Parabéns! Conseguiu desviar de todas as bombas!") :
                              sf::String(L"Sugerimos que procure o hospital mais próximo."));
    centerAtPosition(supportMessage_, 0.5);
    
    // Botão de retorno.
    centerAtPosition(returnButton_, 0.7);
}

GameOverScreen::~GameOverScreen() {}

void GameOverScreen::draw(sf::Vector2i mousePosition, MouseState mouseState) {
    Screen::draw(mousePosition, mouseState);

    if(returnButton_.update(mousePosition) == ButtonState::MouseHovering && mouseState == MouseState::LeftButtonPressed)
        state_ = ScreenState::ChangeToTitle;
    
    window_->draw(mainMessage_);
    window_->draw(supportMessage_);
    window_->draw(returnButton_);
}
