#include "CampoMinado.h"

CampoMinado::CampoMinado(int linhas, int colunas, int qtdBombas) :
    estado_(EstadoJogo::Ocioso), tabuleiro_(linhas, colunas, qtdBombas)  {}

Coord CampoMinado::aguardarJogada() {
    Coord jogada;

    while(true) {
        std::string coord;
        std::cout << "> Informe uma coordenada (ex: A1): ";
        std::getline(std::cin, coord);

        jogada = {coord[1]-'1', coord[0]-'A'};
        if(isJogadaValida(jogada)) break;
    };

    return jogada;
}

void CampoMinado::iniciar() {
    while(estado_ != EstadoJogo::Vitoria && estado_ != EstadoJogo::Derrota) {
        tabuleiro_.apresentar();
        auto jogada = aguardarJogada();
        realizarJogada(jogada);
    }

    tabuleiro_.apresentar(true);
    std::string mensagem = (estado_ == EstadoJogo::Vitoria) ?
                           "Parabéns, você venceu!" :
                           "Infelizmente não foi dessa vez...";
    
    std::cout << mensagem << std::endl;
    std::cout.flush();
}

bool CampoMinado::isJogadaValida(Coord coord) {
    return tabuleiro_.isCoordenadaValida(coord) &&
           tabuleiro_.item(coord).estado() == EstadoItem::NaoSelecionado;
}

void CampoMinado::realizarJogada(Coord coord) {
    auto& item = tabuleiro_.item(coord);
    tabuleiro_.selecionarItem(coord);
    
    if(item.isBomba())
        estado_ = EstadoJogo::Derrota;
    else if(tabuleiro_.isTodosSelecionados())
        estado_ = EstadoJogo::Vitoria;
}