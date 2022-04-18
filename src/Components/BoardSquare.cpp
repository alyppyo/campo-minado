#include "BoardSquare.h"

BoardSquare::BoardSquare() : content_(BoardSquareContent::Empty) {
    float outlineThickness = 1;

    squareOutlineColor_ = Palette::Background;
    squareFillColor_ = Palette::Text;

    size_ = sf::Vector2f(30,30);

    square_.setSize(size_);
    square_.setOutlineThickness(0);
    square_.setOutlineColor(squareOutlineColor_);
    square_.setFillColor(squareFillColor_);

    text_.setFont(AssetManager::font(Font::Roboto));
    text_.setFillColor(squareFillColor_);
    text_.setCharacterSize(24);
}

BoardSquare::~BoardSquare() {}

void BoardSquare::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = getTransform();
    target.draw(square_, states);

    if(flagged_) target.draw(sprite_, states);
    else if(state_ == BoardSquareState::Pressed) {
        if(content_ == BoardSquareContent::Text)
            target.draw(text_, states);
        else if(content_ == BoardSquareContent::Sprite)
            target.draw(sprite_, states);
    }
}

bool BoardSquare::flagged() {
    return flagged_;
}

void BoardSquare::setContent(std::string text) {
    content_ = BoardSquareContent::Text;
    text_.setString(text);
}

void BoardSquare::setContent(sf::Texture& texture) {
    content_ = BoardSquareContent::Sprite;
    sprite_.setTexture(texture);
    sprite_.setScale(0.35,0.35);
}

void BoardSquare::setFlagged(bool flagged) {
    if(flagged) {
        backupContent_ = content_;
        backupSprite_ = sprite_;
        setContent(AssetManager::texture(Texture::Flag));
    }
    else {
        content_ = backupContent_;
        sprite_ = backupSprite_;
    }

    flagged_ = flagged;
}

void BoardSquare::setPosition(sf::Vector2f position) {
    square_.setPosition(position);

    text_.setPosition(position);
    sf::FloatRect bounds = text_.getLocalBounds();
    text_.setOrigin((bounds.width - square_.getSize().x)/2 + bounds.left,
                    (bounds.height - square_.getSize().y)/2 + bounds.top);

    sprite_.setPosition(position);
    bounds = sprite_.getLocalBounds();
    sprite_.move(4,4);
}

sf::Vector2f BoardSquare::size() {
    return size_;
}

void BoardSquare::setState(BoardSquareState state) {
    if(state_ == BoardSquareState::Pressed) return;

    if(state == BoardSquareState::MouseHovering) {
        square_.setOutlineColor(sf::Color(247, 131, 97));
        square_.setOutlineThickness(6);
    }
    else if(state == BoardSquareState::Idle) {
        square_.setOutlineColor(squareOutlineColor_);
        square_.setOutlineThickness(1);
    }
    else if(state == BoardSquareState::Pressed) {
        square_.setOutlineColor(sf::Color::White);
        square_.setOutlineThickness(1);
        square_.setFillColor(Palette::ButtonSelected);
    }

    state_ = state;
}

BoardSquareState BoardSquare::state() {
    return state_;
}