#ifndef BOARD_H
#define BOARD_H

/**
 * @file Board.h
 * @author Alyppyo Coutinho
 * @brief Classe que representa o tabuleiro de um jogo de campo minado.
 * @version 0.1
 * @date 2022-04-18
 */

// C++
#include <algorithm>
#include <array>
#include <iomanip>
#include <numeric>
#include <queue>
#include <random>
#include <vector>

// Projeto
#include "BoardItem.h"

// Alias para coordenadas dadas em pares.
using Coord = std::pair<int,int>;

/**
 * @brief Classe que representa um tabuleiro de campo minado.
 * 
 */
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