#include "AssetManager.h"

sf::Font AssetManager::fonts_[Font::FontCount];
sf::Texture AssetManager::textures_[Texture::TextureCount];

AssetManager::AssetManager() {
    // Load fonts
    std::string fontPath = "../fonts/";

    if(!fonts_[Font::MotionControl].loadFromFile(fontPath + "MotionControl-Bold.otf"))
        std::cout << "Erro ao carregar fonte MotionControl!" << std::endl;
    if(!fonts_[Font::Roboto].loadFromFile(fontPath + "Roboto-Regular.ttf"))
        std::cout << "Erro ao carregar fonte Roboto!" << std::endl;
    if(!fonts_[Font::NotoSans].loadFromFile(fontPath + "NotoSans-Regular.ttf"))
        std::cout << "Erro ao carregar fonte NotoSans!" << std::endl;

    // Load textures
    std::string texturePath = "../img/";

    if(!textures_[Texture::Bomb].loadFromFile(texturePath + "bomb_white.png"))
        std::cout << "Erro ao carregar a textura de bomba!" << std::endl;
    if(!textures_[Texture::Flag].loadFromFile(texturePath + "flag.png"))
        std::cout << "Erro ao carregar a textura de bandeira!" << std::endl;
    if(!textures_[Texture::Logo].loadFromFile(texturePath + "logo.png"))
        std::cout << "Erro ao carregar a textura da logo!" << std::endl;
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