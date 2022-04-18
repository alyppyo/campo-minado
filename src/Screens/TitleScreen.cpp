/**
 * @file TitleScreen.cpp
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Métodos da tela inicial do jogo.
 * @version 0.1
 * @date 2022-04-18
 */

#include "TitleScreen.h"

/**
 * @brief Constrói uma nova tela inicial.
 * 
 * @param window Ponteiro para a janela na qual a tela será desenhada.
 */
TitleScreen::TitleScreen(sf::RenderWindow * window) : Screen::Screen(window) {
    // Configurar a logo.
    logo_.setTexture(AssetManager::texture(Texture::Logo));
    logo_.setPosition(0, 60);

    // Definir tamanho dos caracteres nos botões.
    int characterSize = 50;

    // Criar os botões do menu.
    buttons_.emplace_back(L"Iniciar Jogo", characterSize);
    buttons_.emplace_back(L"Opções", characterSize);

    // Distribuir os botões na tela.
    float height = 0.7;
    for(auto& button : buttons_) {
        centerAtPosition(button, height);
        height += 0.075;
    }
}

/**
 * @brief Desenha a tela.
 * 
 * @param mousePosition Posição do mouse.
 * @param mouseState Estado do mouse.
 */
void TitleScreen::draw(sf::Vector2i mousePosition, MouseState mouseState) {
    // Invoca a função de desenho da classe base.
    Screen::draw(mousePosition, mouseState);

    // Desenha a logo.
    window_->draw(logo_);

    // Desenha os botões.
    for(int i = 0; i < buttons_.size(); ++i) {
        // Atualiza os botões de acordo com a posição e o estado do mouse.
        if(buttons_[i].update(mousePosition) == ButtonState::MouseHovering && mouseState == MouseState::LeftButtonPressed)
            state_ = (i == 0) ? ScreenState::ChangeToGame : ScreenState::ChangeToOptions;

        window_->draw(buttons_[i]);
    }
}
