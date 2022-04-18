/**
 * @file Screen.cpp
 * @author Alyppyo Coutinho
 * @brief Implementação dos métodos da tela base.
 * @version 0.1
 * @date 2022-04-18
 */

#include "Screen.h"

/**
 * @brief Constrói uma nova tela base.
 * 
 * @param window Janela na qual a tela será desenhada.
 */
Screen::Screen(sf::RenderWindow * window) : window_(window), state_(ScreenState::Idle) {}

/**
 * @brief Centraliza um determinado texto (ou botão simples) na horizontal, e o posiciona na vertical
 * de acordo com o valor passado como parâmetro.
 * 
 * @param text Texto ou botão a ser centralizado horizontalmente.
 * @param height Porcentagem da altura da tela na qual será posicionado.
 */
void Screen::centerAtPosition(sf::Text& text, float height) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(bounds.left + bounds.width/2, bounds.top + bounds.height/2));
    text.setPosition(sf::Vector2f(window_->getSize().x*0.5, window_->getSize().y*height));
}

/**
 * @brief Desenha a tela.
 * 
 * @param mousePosition Posição do mouse.
 * @param mouseState Estado do mouse.
 */
void Screen::draw(sf::Vector2i mousePosition, MouseState mouseState) {
    window_->clear(Palette::Background);
}

/**
 * @brief Atualiza o tamanho da tela para abarcar o tabuleiro.
 * 
 * @param width Nova largura da tela.
 * @param height Nova altura da tela.
 */
void Screen::resize(int width, int height) {
    window_->setSize(sf::Vector2u(width, height));
    window_->setView(sf::View(sf::FloatRect(0, 0, width, height)));
}

/**
 * @brief Retorna o estado atual da tela.
 * 
 * @return ScreenState Estado atual da tela.
 */
ScreenState Screen::state() {
    return state_;
}

/**
 * @brief Define o estado atual da tela.
 * 
 * @param state Novo estado da tela.
 */
void Screen::setState(ScreenState state) {
    state_ = state;
}
