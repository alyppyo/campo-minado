#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

/**
 * @file AssetManager.h
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Gerenciador de mídias do jogo.
 * @version 0.1
 * @date 2022-04-18
 */

// SFML
#include <SFML/Graphics.hpp>

// C++
#include <iostream>

/**
 * @brief Fontes disponíveis.
 */
enum Font {
    MotionControl, Roboto, NotoSans, FontCount
};

/**
 * @brief Texturas utilizadas no jogo
 */
enum Texture {
    Bomb, Flag, Logo, TextureCount
};

/**
 * @brief Classe que representa o gerenciador de mídias do jogo. Todo o acesso é dado de métodos static.
 */
class AssetManager {
    static sf::Font fonts_[Font::FontCount];
    static sf::Texture textures_[Texture::TextureCount];

    AssetManager();

public:
    static void loadAssets();
    static sf::Font& font(Font font);
    static sf::Texture& texture(Texture image);
};

#endif