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

#include "TabuleiroItem.h"

using Coord = std::pair<int,int>;

class Tabuleiro {
    int linhas_, colunas_;
    int qtdBombas_, qtdItensSelecionados_;
    std::vector<std::vector<TabuleiroItem>> matriz_;
    std::array<Coord, 8> coordsVizinhos_;

    void calcularNumeroDeBombasAoRedor();
    void distribuirBombas();
    void propagarVazios(Coord coord);

public:
    Tabuleiro(int linhas, int colunas, int qtdBombas);
    ~Tabuleiro();

    void apresentar(bool mostrarTudo = false);
    bool isCoordenadaValida(Coord coord);
    bool isTodosSelecionados();
    TabuleiroItem& item(Coord coord);
    void selecionarItem(Coord coord, bool propagarVazios = true);
};
 
#endif