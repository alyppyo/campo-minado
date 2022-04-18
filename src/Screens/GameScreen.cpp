#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow * window, int lines, int columns, int numberOfBombs) :
    board_(lines, columns, numberOfBombs), Screen::Screen(window) {

    // Board components
    buttonSpace_ = 2;
    headerHeight_ = 100;
    boardMargin_ = 8;
    boardButtons_ = std::vector(board_.lines(), std::vector<Button>(board_.columns()));
    window_ = window;
    status_ = ScreenStatus::Idle;
    
    buttonSize_ = sf::Vector2u(boardButtons_[0][0].size().x, boardButtons_[0][0].size().y);
    boardSize_ = sf::Vector2u(board_.columns()*(buttonSize_.x+buttonSpace_)-buttonSpace_+2*boardMargin_,
                              board_.lines()*(buttonSize_.y+buttonSpace_)-buttonSpace_+2*boardMargin_);

    sf::FloatRect boardArea(0, 0, boardSize_.x, headerHeight_ + boardSize_.y);
    window_->setSize(boardSize_ + sf::Vector2u(0,headerHeight_));
    window_->setView(sf::View(boardArea));

    for(int i = 0; i < board_.lines(); ++i) {
        for(int j = 0; j < board_.columns(); ++j) {
            auto itemContent = board_.item({i,j}).content();
            if(itemContent == ItemContent::Bomb)
                boardButtons_[i][j].setContent(AssetManager::texture(Texture::Bomb));
            else
                boardButtons_[i][j].setContent(std::string(1,itemContent));

            boardButtons_[i][j].setPosition(sf::Vector2f(j*(buttonSize_.x+buttonSpace_)+boardMargin_,
                                                         headerHeight_+i*(buttonSize_.y+buttonSpace_)+boardMargin_));
        }
    }

    // Header components
    sf::Color teal(25,114,120), darkTeal(40,61,59);
    sf::Color red1(245, 75, 100);
    sf::Color red2(247, 131, 97);
    sf::Color gray1(36, 42, 56);
    sf::Color gray2(78, 88, 110);

    auto [windowWidth, windowHeight] = window_->getSize();
    // rectangle_[0] = sf::Vertex(sf::Vector2f(0, 0), red1);
    // rectangle_[1] = sf::Vertex(sf::Vector2f(windowWidth, 0), red1);
    // rectangle_[2] = sf::Vertex(sf::Vector2f(windowWidth, windowHeight), red1);
    // rectangle_[3] = sf::Vertex(sf::Vector2f(0, windowHeight), red1);

    // backgroundRect_.setFillColor(gray1);
    // backgroundRect_.setSize(sf::Vector2f(boardSize_.x, headerHeight_));

    sf::RectangleShape backgroundBombCounter;
    sf::RectangleShape backgroundSpecialistCounter;

    titleBombCounter_.setFont(AssetManager::font(Font::Roboto));
    titleBombCounter_.setString(L"Bombas");
    titleBombCounter_.setCharacterSize(30);
    titleBombCounter_.setFillColor(sf::Color::White);
}

void GameScreen::draw(sf::Vector2i mousePosition, bool mousePressed) {
    Screen::draw(mousePosition, mousePressed); 

    drawHeader();

    int line = (mousePosition.y-headerHeight_-boardMargin_)/(buttonSize_.y+buttonSpace_);
    int column = (mousePosition.x-boardMargin_)/(buttonSize_.x+buttonSpace_);
 
    bool buttonFound = isValidCoord(line, column);

    if(buttonFound) {
        boardButtons_[line][column].setState(mousePressed ? ButtonState::Pressed : ButtonState::MouseHovering);
        
        if(mousePressed)  
            updateBoard(line, column);
    }

    for(int i = 0; i < board_.lines(); ++i) {
        for(int j = 0; j < board_.columns(); ++j) {
            if(buttonFound && i == line && j == column) continue;
            window_->draw(boardButtons_[i][j]);
        }
    }

    if(buttonFound) {
        window_->draw(boardButtons_[line][column]);
        boardButtons_[line][column].setState(ButtonState::MouseOut);

        if(board_.item({line,column}).isBomb() && mousePressed)
            status_ = ScreenStatus::ChangeToGameOverDefeat;
    }
}

void GameScreen::drawHeader() {
    window_->draw(titleBombCounter_);
}

bool GameScreen::isValidCoord(int line, int column) {
    return line > -1 && line < board_.lines() &&
           column > -1 && column < board_.columns();
}

void GameScreen::updateBoard(int line, int column) {
    Coord itemCoord {line,column};
    board_.selectItem(itemCoord);
    
    for(int i = 0; i < board_.lines(); ++i) {
        for(int j = 0; j < board_.columns(); ++j) {
            if(boardButtons_[i][j].state() != ButtonState::Pressed &&
               board_.item({i,j}).state() == ItemState::Selected)
                boardButtons_[i][j].setState(ButtonState::Pressed);
        }
    }   
}