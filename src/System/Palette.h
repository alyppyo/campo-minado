#ifndef PALETTE_H
#define PALETTE_H

/**
 * @file Palette.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Namespace que centraliza as cores utilizadas pelos componentes do jogo.
 * @version 0.1
 * @date 2022-04-18
 */

// SFML
#include <SFML/Graphics.hpp>

/**
 * @brief Namespace que centraliza as cores utilizadas pelos componentes do jogo.
 */
namespace Palette {
    // Game colors.
    const sf::Color red(245, 75, 100);
    const sf::Color orange(247, 131, 97);

    // Color scheme.
    const sf::Color Background(red);
    const sf::Color Text(sf::Color::White);
    const sf::Color ButtonSelected(orange);
};

#endif