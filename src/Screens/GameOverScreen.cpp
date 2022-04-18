#include "GameOverScreen.h"
/**
 * @brief Constrói uma tela de finalização de jogo.
 * 
 * @param window Janela na qual a tela será desenhada.
 * @param victory Indica se a mensagem na tela será de vitória ou derrota.
 */
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

/**
 * @brief Destrutor padrão.
 */
GameOverScreen::~GameOverScreen() {}

/**
 * @brief Desenhar tela.
 * 
 * @param mousePosition Posição do mouse.
 * @param mouseState Estado do mouse.
 */
void GameOverScreen::draw(sf::Vector2i mousePosition, MouseState mouseState) {
    // Invocar método de desenho da classe base.
    Screen::draw(mousePosition, mouseState);

    // Atualizar mouse de acordo com a posição e estado do mouse.
    if(returnButton_.update(mousePosition) == ButtonState::MouseHovering && mouseState == MouseState::LeftButtonPressed)
        state_ = ScreenState::ChangeToTitle;

    // Desenhar itens da tela.    
    window_->draw(mainMessage_);
    window_->draw(supportMessage_);
    window_->draw(returnButton_);
}
