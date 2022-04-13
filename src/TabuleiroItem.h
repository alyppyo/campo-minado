#ifndef TABULEIRO_ITEM_H
#define TABULEIRO_ITEM_H

#include <ostream>

namespace ConteudoItem {
    const char Bandeira = 'B';
    const char Bomba = '*';
    const char Interrogacao = '?';
    const char NaoSelecionado = '#';
    const char Vazio = ' ';
};

enum class EstadoItem {
    NaoSelecionado, Selecionado, MarcadoComBandeira, MarcadoComInterrogacao
};

class TabuleiroItem {
    char conteudo_;
    EstadoItem estado_;

public:
    TabuleiroItem();

    char conteudo() const;
    EstadoItem estado() const;
    bool isBomba();
    void setConteudo(char conteudo);
    void setEstado(EstadoItem estado);

    friend std::ostream& operator<<(std::ostream& out, const TabuleiroItem& item);
};

#endif