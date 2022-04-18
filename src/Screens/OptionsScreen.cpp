#include "OptionsScreen.h"

OptionsScreen::OptionsScreen(sf::RenderWindow * window, int& lines, int& columns, int& bombs, int& specialists) :
    Screen::Screen(window), lines_(lines), columns_(columns), bombs_(bombs), specialists_(specialists) {
    int characterSize = 30;
    auto& labelFont = AssetManager::font(Font::NotoSans);

    // Definição de limites.
    minLines_ = minColumns_ = 10;
    minBombs_ = minSpecialists_ = 0;
    maxLines_ =  maxColumns_ = 25;
    maxBombs_ = maxLines_*maxBombs_;
    maxSpecialists_ = 3;

    // Títulos.
    texts_.emplace_back(L"Opções", AssetManager::font(Font::MotionControl), 80);
    centerAtPosition(texts_.back(), 0.15);

    texts_.emplace_back(L"Linhas", labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.3);

    texts_.emplace_back(sf::String(std::to_string(lines_)), labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.35);

    texts_.emplace_back(L"Colunas", labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.45);

    texts_.emplace_back(sf::String(std::to_string(columns_)), labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.5);

    texts_.emplace_back(L"Bombas", labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.6);

    texts_.emplace_back(sf::String(std::to_string(bombs_)), labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.65);

    texts_.emplace_back(L"Especialistas", labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.75);

    texts_.emplace_back(sf::String(std::to_string(specialists_)), labelFont, characterSize);
    centerAtPosition(texts_.back(), 0.8);

    /* Botões */
    int distanceFromText = 40;

    // Botões das linhas.
    buttons_.emplace_back(L"-", characterSize);
    centerAtPosition(buttons_.back(), 0.35);
    buttons_.back().move(sf::Vector2f(-distanceFromText, 0));

    buttons_.emplace_back(L"+", characterSize);
    centerAtPosition(buttons_.back(), 0.35);
    buttons_.back().move(sf::Vector2f(distanceFromText, 0));

    // Botões das colunas.
    buttons_.emplace_back(L"-", characterSize);
    centerAtPosition(buttons_.back(), 0.5);
    buttons_.back().move(sf::Vector2f(-distanceFromText, 0));

    buttons_.emplace_back(L"+", characterSize);
    centerAtPosition(buttons_.back(), 0.5);
    buttons_.back().move(sf::Vector2f(distanceFromText, 0));

    // Botões das bombas.
    buttons_.emplace_back(L"-", characterSize);
    centerAtPosition(buttons_.back(), 0.65);
    buttons_.back().move(sf::Vector2f(-distanceFromText, 0));

    buttons_.emplace_back(L"+", characterSize);
    centerAtPosition(buttons_.back(), 0.65);
    buttons_.back().move(sf::Vector2f(distanceFromText, 0));

    // Botões dos especialistas.
    buttons_.emplace_back(L"-", characterSize);
    centerAtPosition(buttons_.back(), 0.8);
    buttons_.back().move(sf::Vector2f(-distanceFromText, 0));

    buttons_.emplace_back(L"+", characterSize);
    centerAtPosition(buttons_.back(), 0.8);
    buttons_.back().move(sf::Vector2f(distanceFromText, 0));

    // Botão de retorno à tela inicial.
    buttons_.emplace_back(L"Voltar à tela inicial", characterSize);
    buttons_.back().setFont(AssetManager::font(Font::MotionControl));
    centerAtPosition(buttons_.back(), 0.9);
}

OptionsScreen::~OptionsScreen() {}
    
void OptionsScreen::draw(sf::Vector2i mousePosition, bool mousePressed) {
    Screen::draw(mousePosition, mousePressed);

    for(auto& text : texts_)
        window_->draw(text);

    for(int i = 0; i < buttons_.size(); ++i) {
        if(buttons_[i].update(mousePosition) == ButtonState::MouseHovering && mousePressed) {
            if(i == 0 && lines_ > minLines_) {
                --lines_;
                texts_[2].setString(sf::String(std::to_string(lines_)));

                maxBombs_ = lines_*columns_;
                if(maxBombs_ < bombs_) {
                    bombs_ = maxBombs_;
                    texts_[6].setString(sf::String(std::to_string(bombs_)));
                }
            }
            else if(i == 1 && lines_ < maxLines_) {
                ++lines_;
                texts_[2].setString(sf::String(std::to_string(lines_)));

                maxBombs_ = lines_*columns_;
            }
            else if(i == 2 && columns_ > minColumns_) {
                --columns_;
                texts_[4].setString(sf::String(std::to_string(columns_)));

                maxBombs_ = lines_*columns_;
                if(maxBombs_ < bombs_) {
                    bombs_ = maxBombs_;
                    texts_[6].setString(sf::String(std::to_string(bombs_)));
                }
            }
            else if(i == 3 && columns_ < maxColumns_) {
                ++columns_;
                texts_[4].setString(sf::String(std::to_string(columns_)));

                maxBombs_ = lines_*columns_;
            }
            else if(i == 4 && bombs_ > minBombs_) {
                --bombs_;
                texts_[6].setString(sf::String(std::to_string(bombs_)));
            }
            else if(i == 5 && bombs_ < maxBombs_) {
                ++bombs_;
                texts_[6].setString(sf::String(std::to_string(bombs_)));
            }
            else if(i == 6 && specialists_ > minSpecialists_) {
                --specialists_;
                texts_[8].setString(sf::String(std::to_string(specialists_)));
            }
            else if(i == 7 && specialists_ < maxSpecialists_) {
                ++specialists_;
                texts_[8].setString(sf::String(std::to_string(specialists_)));
            }
            else if(i == 8)
                status_ = ScreenStatus::ChangeToTitle;
        }

        window_->draw(buttons_[i]);
    }
}
