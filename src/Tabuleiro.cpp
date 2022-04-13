#include "Tabuleiro.h"

Tabuleiro::Tabuleiro(int linhas, int colunas, int qtdBombas) :
    linhas_(linhas), colunas_(colunas), qtdBombas_(qtdBombas),
    qtdItensSelecionados_(0), matriz_(linhas, std::vector<TabuleiroItem>(colunas)),
    coordsVizinhos_({Coord{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}}) {
    distribuirBombas();
    calcularNumeroDeBombasAoRedor();
}

Tabuleiro::~Tabuleiro() {}

void Tabuleiro::apresentar(bool mostrarTudo) {
    std::cout << "   ";
    for(int i = 0; i < colunas_; ++i)
        std::cout << " | " << char('A'+i);
    std::cout << " | " << std::endl;

    for(int i = 0; i < linhas_; ++i) {
        std::cout << std::setw(3) << (i+1) << " | ";
        for(int j = 0; j < colunas_; ++j) {            
            if(mostrarTudo)
                std::cout << matriz_[i][j]; 
            else {    
                switch(matriz_[i][j].estado()) {
                    case EstadoItem::NaoSelecionado:
                        std::cout << ConteudoItem::NaoSelecionado; break;
                    case EstadoItem::Selecionado:
                        std::cout << matriz_[i][j]; break;
                    case EstadoItem::MarcadoComBandeira:
                        std::cout << ConteudoItem::Bandeira; break;
                    case EstadoItem::MarcadoComInterrogacao:
                        std::cout << ConteudoItem::Interrogacao; break;
                }
            }
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}

void Tabuleiro::calcularNumeroDeBombasAoRedor() {
    for(int i = 0; i < linhas_; ++i) {
        for(int j = 0; j < colunas_; ++j) {
            if(matriz_[i][j].isBomba()) continue;

            int numBombas = 0;
            for(auto [di, dj] : coordsVizinhos_) {
                Coord coord {i+di, j+dj};
                if(isCoordenadaValida(coord) && matriz_[coord.first][coord.second].isBomba()) 
                    ++numBombas;
            }

            matriz_[i][j].setConteudo((numBombas == 0) ? ConteudoItem::Vazio : '0'+numBombas);           
        }
    }
}

void Tabuleiro::distribuirBombas() {
    std::string items(linhas_*colunas_, ConteudoItem::Vazio);

    for(int i = 0; i < qtdBombas_; ++i)
        items[i] = ConteudoItem::Bomba;

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::shuffle(items.begin(), items.end(), generator);

    auto it = items.begin();
    for(int i = 0; i < linhas_; ++i) {
        for(int j = 0; j < colunas_; ++j, ++it) {
            if(*it == ConteudoItem::Bomba)
                matriz_[i][j].setConteudo(ConteudoItem::Bomba);
        }
    }
}

bool Tabuleiro::isCoordenadaValida(Coord coord) {
    return coord.first  > -1 && coord.first  < linhas_ &&
           coord.second > -1 && coord.second < colunas_;
}

bool Tabuleiro::isTodosSelecionados() {
    return (linhas_*colunas_ - qtdItensSelecionados_) == qtdBombas_;
}

TabuleiroItem& Tabuleiro::item(Coord coord) {
    return matriz_[coord.first][coord.second];
}

void Tabuleiro::propagarVazios(Coord coord) {
    std::queue<Coord> proximos;
    proximos.push(coord);

    while(!proximos.empty()) {
        coord = proximos.front();

        for(auto [di, dj] : coordsVizinhos_) {
            Coord coordVizinho {coord.first+di, coord.second+dj};
            if(!isCoordenadaValida(coordVizinho)) continue;

            auto& vizinho = item(coordVizinho);

            if(vizinho.estado() == EstadoItem::NaoSelecionado && !vizinho.isBomba()) {
                selecionarItem(coordVizinho, false);
                if(vizinho.conteudo() == ConteudoItem::Vazio)
                    proximos.push(coordVizinho);
            }
        }

        proximos.pop();
    }
}

void Tabuleiro::selecionarItem(Coord coord, bool propagar) {
    auto& tabuleiroItem = item(coord);
    tabuleiroItem.setEstado(EstadoItem::Selecionado);
    ++qtdItensSelecionados_;

    if(propagar && tabuleiroItem.conteudo() == ConteudoItem::Vazio)
        propagarVazios(coord);
}