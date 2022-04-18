/**
 * @file BoardSquare.cpp
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Implementação da classe que representa uma casa do tabuleiro do campo minado.
 * @version 0.1
 * @date 2022-04-18
 */

#include "BoardSquare.h"

/**
 * @brief Constrói uma casa do tabuleiro.
 */
BoardSquare::BoardSquare() : content_(BoardSquareContent::Empty) {
    // Definição dos parâmetros iniciais.
    float outlineThickness = 1;
    squareOutlineColor_ = Palette::Background;
    squareFillColor_ = Palette::Text;
    size_ = sf::Vector2f(30,30);

    // Configuração do quadrado que representará a casa.
    square_.setSize(size_);
    square_.setOutlineThickness(0);
    square_.setOutlineColor(squareOutlineColor_);
    square_.setFillColor(squareFillColor_);

    // Configuração do texto que poderá aparecer de acordo com o conteúdo.
    text_.setFont(AssetManager::font(Font::Roboto));
    text_.setFillColor(squareFillColor_);
    text_.setCharacterSize(24);
}

/**
 * @brief Destrutor padrão.
 */
BoardSquare::~BoardSquare() {}

/**
 * @brief Responsável por desenhar a casa.
 * 
 * @param target Objeto responsável pelo desenho.
 * @param states Estados atuais aplicados ao objeto.
 */
void BoardSquare::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Desenhar o plano de fundo.
    states.transform = getTransform();
    target.draw(square_, states);

    // Se a casa estiver marcada com uma bandeira, desenhar o conteúdo da sprite.
    if(flagged_) target.draw(sprite_, states);
    // Caso contrário, se ela está pressionada, pode-se desenhar o texto indicando
    // quantas bombas há ao redor ou a própria bomba.
    else if(state_ == BoardSquareState::Pressed) {
        if(content_ == BoardSquareContent::Text)
            target.draw(text_, states);
        else if(content_ == BoardSquareContent::Sprite)
            target.draw(sprite_, states);
    }
}

/**
 * @brief Indica se a casa está marcada com bandeira.
 * 
 * @return True, se está marcada. Falso, caso não esteja.
 */
bool BoardSquare::flagged() {
    return flagged_;
}

/**
 * @brief Define que o conteúdo da casa será um texto.
 * 
 * @param text Texto a ser definido como conteúdo.
 */
void BoardSquare::setContent(std::string text) {
    content_ = BoardSquareContent::Text;
    text_.setString(text);
}

/**
 * @brief Define que o conteúdo da casa será uma textura.
 * 
 * @param texture Textura a ser definida como conteúdo.
 */
void BoardSquare::setContent(sf::Texture& texture) {
    content_ = BoardSquareContent::Sprite;
    sprite_.setTexture(texture);
    sprite_.setScale(0.35,0.35);
}

/**
 * @brief Define se a casa será marcada como bandeira.
 * 
 * @param flagged Indica se a bandeira será ativada ou desativada.
 */
void BoardSquare::setFlagged(bool flagged) {
    // Caso se deseje marcar a casa, é necessário guardar o seu
    // conteúdo temporariamente em um backup.
    if(flagged) {
        backupContent_ = content_;
        backupSprite_ = sprite_;
        setContent(AssetManager::texture(Texture::Flag));
    }
    // Ao se desmarcar a casa, o conteúdo original é restaurado.
    else {
        content_ = backupContent_;
        sprite_ = backupSprite_;
    }

    // Define a marcação da casa.
    flagged_ = flagged;
}

/**
 * @brief Define a posição da casa na janela.
 * 
 * @param position Posição desejada da casa na janela.
 */
void BoardSquare::setPosition(sf::Vector2f position) {
    // Define posição geral da casa.
    square_.setPosition(position);

    // Define posição do conteúdo textual, centralizado no quadrado de plano de fundo.
    text_.setPosition(position);
    sf::FloatRect bounds = text_.getLocalBounds();
    text_.setOrigin((bounds.width - square_.getSize().x)/2 + bounds.left,
                    (bounds.height - square_.getSize().y)/2 + bounds.top);

    // Define posição do conteúdo gráfico.
    sprite_.setPosition(position);
    bounds = sprite_.getLocalBounds();
    sprite_.move(4,4);
}

/**
 * @brief Retorna as dimensões da casa.
 * 
 * @return sf::Vector2f Dimensões da casa.
 */
sf::Vector2f BoardSquare::size() {
    return size_;
}

/**
 * @brief Define o estado da casa.
 * 
 * @param state Novo estado no qual a casa se encontrará.
 */
void BoardSquare::setState(BoardSquareState state) {
    // Caso o estado atual da casa já seja pressionado, nada deve ser feito.
    if(state_ == BoardSquareState::Pressed) return;

    // Caso o mouse esteja em cima, desenhar o contorno.
    if(state == BoardSquareState::MouseHovering) {
        square_.setOutlineColor(sf::Color(247, 131, 97));
        square_.setOutlineThickness(6);
    }
    // Caso o novo estado seja "ociosa", voltar à aparência padrão.
    else if(state == BoardSquareState::Idle) {
        square_.setOutlineColor(squareOutlineColor_);
        square_.setOutlineThickness(1);
    }
    // Caso o novo estado seja "pressionada", definir a aparência final da casa.
    else if(state == BoardSquareState::Pressed) {
        square_.setOutlineColor(sf::Color::White);
        square_.setOutlineThickness(1);
        square_.setFillColor(Palette::ButtonSelected);
    }

    // Definir estado.
    state_ = state;
}

/**
 * @brief Retorna o estado atual da casa.
 * 
 * @return BoardSquareState Estado atual da casa.
 */
BoardSquareState BoardSquare::state() {
    return state_;
}
