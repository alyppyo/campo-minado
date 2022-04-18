#include "AssetManager.h"

sf::Font AssetManager::fonts_[3];
sf::Texture AssetManager::textures_[2];

AssetManager::AssetManager() {
    // Load fonts
    std::string fontPath = "../fonts/";

    if(!fonts_[Font::MotionControl].loadFromFile(fontPath + "MotionControl-Bold.otf"))
        std::cout << "Erro ao carregar fonte MotionControl!" << std::endl;
    if(!fonts_[Font::Roboto].loadFromFile(fontPath + "Roboto-Regular.ttf"))
        std::cout << "Erro ao carregar fonte Roboto!" << std::endl;
    if(!fonts_[Font::Awesome].loadFromFile(fontPath + "Font Awesome 6 Free-Regular-400.otf"))
        std::cout << "Erro ao carregar fonte NotoEmoji!" << std::endl;

    // Load textures
    std::string texturePath = "../img/";

    if(!textures_[Texture::Bomb].loadFromFile(texturePath + "bomb_white.png"))
        std::cout << "Erro ao carregar a textura de bomba!" << std::endl;
    if(!textures_[Texture::Flag].loadFromFile(texturePath + "bomb_red.png"))
        std::cout << "Erro ao carregar a textura de bandeira!" << std::endl;
}

void AssetManager::loadAssets() {
    static AssetManager assetManager;
}

sf::Font& AssetManager::font(Font font) {
    return AssetManager::fonts_[font];
}

sf::Texture& AssetManager::texture(Texture image) {
    return AssetManager::textures_[image];
}