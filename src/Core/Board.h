#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <vector>

#include "BoardItem.h"

using Coord = std::pair<int,int>;

class Board {
    int lines_, columns_;
    int bombs_, specialists_, numberOfSelectedItems_;
    std::vector<std::vector<BoardItem>> matrix_;
    std::array<Coord, 8> coordsNeighbors_;

    void getNumberOfBombNeighbors();
    void distributeBombs();
    void propagateEmptySpaces(Coord coord);

public:
    Board(int lines, int columns, int bombs, int specialists);
    ~Board();

    bool areAllSelected();
    int columns();
    void decreaseSpecialistsNumber();
    bool isValidCoord(Coord coord);
    BoardItem& item(Coord coord);
    int lines();
    void selectItem(Coord coord, bool propagateEmptySpaces = true); 
    void setFlag(Coord coord, bool active);
    int specialists();
};
 
#endif