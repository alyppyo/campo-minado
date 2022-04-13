#include "TabuleiroItem.h"

TabuleiroItem::TabuleiroItem() :
    conteudo_(ConteudoItem::Vazio), estado_(EstadoItem::NaoSelecionado) {}

char TabuleiroItem::conteudo() const {
    return conteudo_;
}

EstadoItem TabuleiroItem::estado() const {
    return estado_;
}

bool TabuleiroItem::isBomba() {
    return conteudo_ == ConteudoItem::Bomba;
}

void TabuleiroItem::setConteudo(char conteudo) {
    conteudo_ = conteudo;
}

void TabuleiroItem::setEstado(EstadoItem estado) {
    estado_ = estado;
}

std::ostream& operator<<(std::ostream& out, const TabuleiroItem& item) {
    out << static_cast<char>(item.conteudo());
    return out;
}