#ifndef CAMPO_MINADO_H
#define CAMPO_MINADO_H

#include <iostream>
#include <string>
#include "Tabuleiro.h"

enum class EstadoJogo {
    Ocioso, EmExecucao, Pausado, Vitoria, Derrota
};

class CampoMinado {
    EstadoJogo estado_;
    Tabuleiro tabuleiro_;

public:
    CampoMinado(int linhas, int colunas, int qtdBombas);

    void iniciar();
    Coord aguardarJogada();
    bool isJogadaValida(Coord coord);
    void realizarJogada(Coord coord);
};

#endif