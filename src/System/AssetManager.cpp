/**
 * @file AssetManager.cpp
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Implementação dos métodos do gerenciador de mídias.
 * @version 0.1
 * @date 2022-04-18
 */

#include "AssetManager.h"

/**
 * @brief Array contendo as fontes utilizadas no projeto.
 */
sf::Font AssetManager::fonts_[Font::FontCount];
/**
 * @brief Array contendo as texturas utilizadas no projeto.
 */
sf::Texture AssetManager::textures_[Texture::TextureCount];

/**
 * @brief Constrói um novo gerenciador de mídia.
 */
AssetManager::AssetManager() {
    // Caminho para o diretório das fontes.
    std::string fontPath = "../fonts/";

    // Tenta carregar as fontes e envia uma mensagem caso ocorra algum problema.
    if(!fonts_[Font::MotionControl].loadFromFile(fontPath + "MotionControl-Bold.otf"))
        std::cout << "Erro ao carregar fonte MotionControl!" << std::endl;
    if(!fonts_[Font::Roboto].loadFromFile(fontPath + "Roboto-Regular.ttf"))
        std::cout << "Erro ao carregar fonte Roboto!" << std::endl;
    if(!fonts_[Font::NotoSans].loadFromFile(fontPath + "NotoSans-Regular.ttf"))
        std::cout << "Erro ao carregar fonte NotoSans!" << std::endl;

    // Caminho para o diretório das imagens.
    std::string texturePath = "../img/";

    // Tenta carregar as textura e envia uma mensagem caso ocorra algum problema.
    if(!textures_[Texture::Bomb].loadFromFile(texturePath + "bomb_white.png"))
        std::cout << "Erro ao carregar a textura de bomba!" << std::endl;
    if(!textures_[Texture::Flag].loadFromFile(texturePath + "flag.png"))
        std::cout << "Erro ao carregar a textura de bandeira!" << std::endl;
    if(!textures_[Texture::Logo].loadFromFile(texturePath + "logo.png"))
        std::cout << "Erro ao carregar a textura da logo!" << std::endl;
}

/**
 * @brief Cria uma versão static do gerenciador de mídias, evitando duplicação.
 */
void AssetManager::loadAssets() {
    static AssetManager assetManager;
}

/**
 * @brief Retorna a fonte indicada no parâmetro.
 * 
 * @param font Indicação da fonte desejada.
 * @return sf::Font& A fonte escolhida.
 */
sf::Font& AssetManager::font(Font font) {
    return AssetManager::fonts_[font];
}

/**
 * @brief Retorna a textura indicada no parâmetro.
 * 
 * @param image Indicação da textura desejada.
 * @return sf::Texture& A textura escolhida.
 */
sf::Texture& AssetManager::texture(Texture image) {
    return AssetManager::textures_[image];
}