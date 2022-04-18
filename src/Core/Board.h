#ifndef TABULEIRO_H
#define TABULEIRO_H

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
    int numberOfBombs_, numberOfSelectedItems_;
    std::vector<std::vector<BoardItem>> matrix_;
    std::array<Coord, 8> coordsNeighbors_;

    void getNumberOfBombNeighbors();
    void distributeBombs();
    void propagateEmptySpaces(Coord coord);

public:
    Board(int linhas, int colunas, int qtdBombas);
    ~Board();

    void show(bool revealBoard = false);
    void selectItem(Coord coord, bool propagateEmptySpaces = true);
    
    int columns();
    BoardItem& item(Coord coord);
    int lines();
    
    bool isValidCoord(Coord coord);
    bool areAllSelected();
};
 
#endif