#include "Board.h"

Board::Board(int lines, int columns, int numberOfBombs) :
    lines_(lines), columns_(columns), numberOfBombs_(numberOfBombs),
    numberOfSelectedItems_(0), matrix_(lines, std::vector<BoardItem>(columns)),
    coordsNeighbors_({Coord{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}}) {
    distributeBombs();
    getNumberOfBombNeighbors();
}

Board::~Board() {}

void Board::show(bool revealBoard) {
    std::cout << "   ";
    for(int i = 0; i < columns_; ++i)
        std::cout << " | " << char('A'+i);
    std::cout << " | " << std::endl;

    for(int i = 0; i < lines_; ++i) {
        std::cout << std::setw(3) << (i+1) << " | ";
        for(int j = 0; j < columns_; ++j) {            
            if(revealBoard)
                std::cout << matrix_[i][j]; 
            else {    
                switch(matrix_[i][j].state()) {
                    case ItemState::NotSelected:
                        std::cout << ItemContent::NotSelected; break;
                    case ItemState::Selected:
                        std::cout << matrix_[i][j]; break;
                    case ItemState::Flagged:
                        std::cout << ItemContent::Flag; break;
                    case ItemState::QuestionMarked:
                        std::cout << ItemContent::QuestionMark; break;
                }
            }
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

void Board::getNumberOfBombNeighbors() {
    for(int i = 0; i < lines_; ++i) {
        for(int j = 0; j < columns_; ++j) {
            if(matrix_[i][j].isBomb()) continue;

            int numBombs = 0;
            for(auto [di, dj] : coordsNeighbors_) {
                Coord coord {i+di, j+dj};
                if(isValidCoord(coord) && matrix_[coord.first][coord.second].isBomb()) 
                    ++numBombs;
            }

            matrix_[i][j].setContent((numBombs == 0) ? ItemContent::Empty : '0'+numBombs);           
        }
    }
}

int Board::columns() {
    return columns_;
}

void Board::distributeBombs() {
    std::string items(lines_*columns_, ItemContent::Empty);

    for(int i = 0; i < numberOfBombs_; ++i)
        items[i] = ItemContent::Bomb;

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::shuffle(items.begin(), items.end(), generator);

    auto it = items.begin();
    for(int i = 0; i < lines_; ++i) {
        for(int j = 0; j < columns_; ++j, ++it) {
            if(*it == ItemContent::Bomb)
                matrix_[i][j].setContent(ItemContent::Bomb);
        }
    }
}

bool Board::isValidCoord(Coord coord) {
    return coord.first  > -1 && coord.first  < lines_ &&
           coord.second > -1 && coord.second < columns_;
}

bool Board::areAllSelected() {
    return (lines_*columns_ - numberOfSelectedItems_) == numberOfBombs_;
}

BoardItem& Board::item(Coord coord) {
    return matrix_[coord.first][coord.second];
}

int Board::lines() {
    return lines_;
}

void Board::propagateEmptySpaces(Coord coord) {
    std::queue<Coord> next;
    next.push(coord);

    while(!next.empty()) {
        coord = next.front();

        for(auto [di, dj] : coordsNeighbors_) {
            Coord coordNeighbor {coord.first+di, coord.second+dj};
            if(!isValidCoord(coordNeighbor)) continue;

            auto& neighbor = item(coordNeighbor);

            if(neighbor.state() == ItemState::NotSelected && !neighbor.isBomb()) {
                selectItem(coordNeighbor, false);
                if(neighbor.content() == ItemContent::Empty)
                    next.push(coordNeighbor);
            }
        }

        next.pop();
    }
}

void Board::selectItem(Coord coord, bool propagar) {
    auto& tabuleiroItem = item(coord);
    tabuleiroItem.setState(ItemState::Selected);
    ++numberOfSelectedItems_;

    if(propagar && tabuleiroItem.content() == ItemContent::Empty)
        propagateEmptySpaces(coord);
}
