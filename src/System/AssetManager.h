#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>

enum Font {
    MotionControl, Roboto, Awesome
};

enum Texture {
    Bomb, Flag
};

class AssetManager {
    static sf::Font fonts_[3];
    static sf::Texture textures_[2];

    AssetManager();

public:
    static void loadAssets();
    static sf::Font& font(Font font);
    static sf::Texture& texture(Texture image);
};

#endif