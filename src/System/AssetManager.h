#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>

enum Font {
    MotionControl, Roboto, NotoSans, FontCount
};

enum Texture {
    Bomb, Flag, Logo, TextureCount
};

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