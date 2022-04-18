#ifndef BOARD_SQUARE_H
#define BOARD_SQUARE_H

/**
 * @file BoardSquare.h
 * @author Alyppyo Coutinho (Alyppyo Coutinho)
 * @brief Classe que representa uma casa do tabuleiro do campo minado.
 * @version 0.1
 * @date 2022-04-18
 */

// SFML
#include <SFML/Graphics.hpp>

// Projeto
#include "../System/AssetManager.h"
#include "../System/Palette.h"

/**
 * @brief Estado da casa do tabuleiro.
 */
enum class BoardSquareState {
    Idle, MouseHovering, Pressed
};

/**
 * @brief Tipo de conteúdo da casa.
 */
enum class BoardSquareContent {
    Empty, Text, Sprite
};

/**
 * @brief Classe que representa a casa do tabuleiro.
 */
class BoardSquare : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape square_; 
    BoardSquareState state_;
    BoardSquareContent content_, backupContent_;
    sf::Color squareOutlineColor_, squareFillColor_;
    sf::Vector2f size_;
    sf::Text text_;
    sf::Sprite sprite_, backupSprite_;
    bool flagged_;

public:
    BoardSquare();
    ~BoardSquare();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    bool flagged();
    sf::Vector2f size();
    BoardSquareState state();
    void setContent(std::string text);
    void setContent(sf::Texture& texture);
    void setFlagged(bool flagged);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setState(BoardSquareState state);
};

#endif