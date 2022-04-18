#include "Button.h"

Button::Button() : content_(ButtonContent::Empty) {
    float outlineThickness = 1;

    // sf::Color red2(247, 131, 97);
    // sf::Color red3(205, 35, 60);

    squareOutlineColor_ = sf::Color(245, 75, 100);
    squareFillColor_ = sf::Color::White;

    size_ = sf::Vector2f(30,30);

    square_.setSize(size_);
    square_.setOutlineThickness(0);
    square_.setOutlineColor(squareOutlineColor_);
    square_.setFillColor(squareFillColor_);

    text_.setFont(AssetManager::font(Font::Roboto));
    text_.setFillColor(squareFillColor_);
    text_.setCharacterSize(24);
}

Button::~Button() {}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = getTransform();
    target.draw(square_, states);

    if(state_ == ButtonState::Pressed) {
        if(content_ == ButtonContent::Text)
            target.draw(text_, states);
        else if(content_ == ButtonContent::Sprite)
            target.draw(sprite_, states);
    }
}

void Button::setContent(std::string text) {
    content_ = ButtonContent::Text;
    text_.setString(text);
}

void Button::setContent(sf::Texture& texture) {
    content_ = ButtonContent::Sprite;
    sprite_.setTexture(texture);
    sprite_.setScale(0.35,0.35);
}

void Button::setPosition(sf::Vector2f position) {
    square_.setPosition(position);

    text_.setPosition(position);
    sf::FloatRect bounds = text_.getLocalBounds();
    text_.setOrigin((bounds.width - square_.getSize().x)/2 + bounds.left,
                    (bounds.height - square_.getSize().y)/2 + bounds.top);

    sprite_.setPosition(position);
    bounds = sprite_.getLocalBounds();
    sprite_.move(4,4);
}

sf::Vector2f Button::size() {
    return size_;
}

void Button::setState(ButtonState state) {
    if(state_ == ButtonState::Pressed) return;

    if(state == ButtonState::MouseHovering) {
        square_.setOutlineColor(sf::Color(247, 131, 97));
        square_.setOutlineThickness(6);
    }
    else if(state == ButtonState::MouseOut) {
        square_.setOutlineColor(squareOutlineColor_);
        square_.setOutlineThickness(1);
    }
    else if(state == ButtonState::Pressed) {
        square_.setOutlineColor(sf::Color::White);
        square_.setOutlineThickness(1);
        square_.setFillColor(sf::Color(247,131,97,100));
    }

    state_ = state;
}

ButtonState Button::state() {
    return state_;
}