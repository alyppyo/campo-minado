#ifndef PALETTE_H
#define PALETTE_H

#include <SFML/Graphics.hpp>

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