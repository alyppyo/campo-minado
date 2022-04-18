#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "Screen.h"
#include "../Core/Board.h"
#include "../Components/BoardSquare.h"
#include "../System/AssetManager.h"

class GameScreen : public Screen {
    std::vector<std::vector<BoardSquare>> boardButtons_;
    Board board_;
    sf::Vector2u boardSize_, buttonSize_;
    int buttonSpace_;
    int boardMargin_;
    int headerHeight_;

    sf::RectangleShape backgroundRect_;
    sf::Text bombsCounterLabel_;
    sf::Text specialistsCounterLabel_;

public:
    GameScreen(sf::RenderWindow * window, int lines, int columns, int bombs, int specialists);
    void drawHeader();
    bool isValidCoord(int line, int column);
    void updateBoard(int line, int column);
    
    virtual void draw(sf::Vector2i mousePosition, bool mousePressed = false) override;
};

#endif
