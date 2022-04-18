/**
 * @file Board.cpp
 * @author Alyppyo Coutinho (alyppyo@gmail.com)
 * @brief Implementação dos métodos da classe que representa o tabuleiro do Campo Minado.
 * @version 0.1
 * @date 2022-04-18
 */

#include "Board.h"

/**
 * @brief Constrói um novo tabuleiro.
 * 
 * @param lines Quantidade de linhas do tabuleiro.
 * @param columns Quantidade de colunas do tabuleiro.
 * @param bombs Quantidade de bombas do tabuleiro.
 * @param specialists Quantidade de especialistas disponíveis.
 */
Board::Board(int lines, int columns, int bombs, int specialists) :
    lines_(lines), columns_(columns), bombs_(bombs), specialists_(specialists),
    numberOfSelectedItems_(0), matrix_(lines, std::vector<BoardItem>(columns)),
    // Coordenadas relativas dos 8 vizinhos de uma casa.
    coordsNeighbors_({Coord{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}}) {
    // Distribuir bombas aleatoriamente.
    distributeBombs();
    // Definir número de bombas vizinhas a cada casa.
    getNumberOfBombNeighbors();
}

/**
 * @brief Destrutor padrão.
 */
Board::~Board() {}

/**
 * @brief Calcula a quantidade de bombas nas casas vizinhas.
 */
void Board::getNumberOfBombNeighbors() {
    // Percorrer todo o tabuleiro.
    for(int i = 0; i < lines_; ++i) {
        for(int j = 0; j < columns_; ++j) {
            // Caso a casa seja uma bomba, não é necessário contar as bombas ao seu redor.
            if(matrix_[i][j].isBomb()) continue;

            // Contar bombas nos vizinhos para cada coordenada válida.
            int numBombs = 0;
            for(auto [di, dj] : coordsNeighbors_) {
                Coord coord {i+di, j+dj};
                if(isValidCoord(coord) && matrix_[coord.first][coord.second].isBomb()) 
                    ++numBombs;
            }

            // Definir o conteúdo da matriz lógica do jogo baseado no número de bombas vizinhas calculadas.
            matrix_[i][j].setContent((numBombs == 0) ? ItemContent::Empty : '0'+numBombs);           
        }
    }
}

/**
 * @brief Retorna a quantidade de colunas do tabuleiro.
 * 
 * @return int Quantidade de colunas do tabuleiro.
 */
int Board::columns() {
    return columns_;
}

/**
 * @brief Diminui em uma unidade a quantidade de especialistas disponíveis, caso ainda haja algum.
 */
void Board::decreaseSpecialistsNumber() {
    if(specialists_ > 0) --specialists_;
}

/**
 * @brief Distribui as bombas aleatoriamente no tabuleiro.
 */
void Board::distributeBombs() {
    // Primeiramente, uma string é criada contendo a mesma quantidade de caracteres
    // que a quantidade de casas no tabuleiro. Seu conteúdo é todo iniciado com o 
    // caractere que representa o vazio.
    std::string items(lines_*columns_, ItemContent::Empty);

    // As primeiras casas são preenchidas com bombas, de acordo com o número definido.
    for(int i = 0; i < bombs_; ++i)
        items[i] = ItemContent::Bomb;

    // Um gerador de números aleatórios é criado e a função "shuffle" embaralha os caracteres da string.
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::shuffle(items.begin(), items.end(), generator);

    // De acordo com a nova disposição dos caracteres da string, as bombas são inseridas no tabuleiro.
    auto it = items.begin();
    for(int i = 0; i < lines_; ++i) {
        for(int j = 0; j < columns_; ++j, ++it) {
            if(*it == ItemContent::Bomb)
                matrix_[i][j].setContent(ItemContent::Bomb);
        }
    }
}

/**
 * @brief Verifica se uma determinada coordenada está dentro dos limites do tabuleiro.
 * 
 * @param coord Coordenada a ser verificada.
 * @return Resultado da checagem. Verdadeiro, caso esteja dentro. Falso, caso contrário.
 */
bool Board::isValidCoord(Coord coord) {
    return coord.first  > -1 && coord.first  < lines_ &&
           coord.second > -1 && coord.second < columns_;
}

/**
 * @brief Verifica se todos os elementos que não são bombas foram selecionados.
 * 
 * @return Verdadeiro, caso todos os itens tenham sido selecionados. Falso, caso contrário.
 */
bool Board::areAllSelected() {
    return (lines_*columns_ - numberOfSelectedItems_) == bombs_;
}

/**
 * @brief Retorna um item do tabuleiro.
 * 
 * @param coord Coordenada do item.
 * @return BoardItem& Referência para o item solicitado.
 */
BoardItem& Board::item(Coord coord) {
    return matrix_[coord.first][coord.second];
}

/**
 * @brief Retorna a quantidade de linhas do tabuleiro.
 * 
 * @return int Quantidade de linhas do tabuleiro.
 */
int Board::lines() {
    return lines_;
}

/**
 * @brief Expande a verificação de bombas para todos os vizinhos que também estejam vazios.
 * 
 * @param coord Coordenada da casa inicial.
 */
void Board::propagateEmptySpaces(Coord coord) {
    // Criação de fila para receber todas os vizinhos possíveis.
    std::queue<Coord> next;
    next.push(coord);

    // Enquanto a fila não estiver vazia, pega uma das coordenadas e verifica seus vizinhos.
    while(!next.empty()) {
        // Pega a primeira coordenada da fila.
        coord = next.front();

        // Verificar todos os possíveis vizinhos.
        for(auto [di, dj] : coordsNeighbors_) {
            Coord coordNeighbor {coord.first+di, coord.second+dj};
            if(!isValidCoord(coordNeighbor)) continue;

            // Caso seja um vizinho válido, não esteja selecionado e não seja uma bomba,
            // ele pode ser selecionado.
            auto& neighbor = item(coordNeighbor);

            if(neighbor.state() == ItemState::NotSelected && !neighbor.isBomb()) {
                selectItem(coordNeighbor, false);
                if(neighbor.content() == ItemContent::Empty)
                    next.push(coordNeighbor);
            }
        }

        // Remove a coordenada que acabou de ser utilizada.
        next.pop();
    }
}

/**
 * @brief Muda o status de um item do tabuleiro para "selecionado".
 * 
 * @param coord Coordenada do item a ser selecionado.
 * @param propagar Indica se o processo de seleção deve ser propagado a seus vizinhos.
 */
void Board::selectItem(Coord coord, bool propagar) {
    auto& boardItem = item(coord);
    boardItem.setState(ItemState::Selected);

    // Se o item selecionado for uma bomba, isso não deve afetar o contador de itens selecionados.
    // Essa verificação adicional é necessária devido aos especialistas, que podem desarmar as bombas.
    if(!boardItem.isBomb()) ++numberOfSelectedItems_;

    // Se o conteúdo do item é vazio, propagar a seus vizinhos.
    if(propagar && boardItem.content() == ItemContent::Empty)
        propagateEmptySpaces(coord);
}

/**
 * @brief Ativar ou remover uma bandeira na casa.
 * 
 * @param coord Coordenada da casa.
 * @param active Indicação de ativação ou desativação da bandeira.
 */
void Board::setFlag(Coord coord, bool active) {
    auto& tabuleiroItem = item(coord);

    // Ativar ou desativar uma bandeira afeta o número de itens selecionados.
    if(active) {
        tabuleiroItem.setState(ItemState::Flagged);
        ++numberOfSelectedItems_;
    }
    else {
        tabuleiroItem.setState(ItemState::NotSelected);
        --numberOfSelectedItems_;
    }
}

/**
 * @brief Retorna a quantidade de especialistas disponíveis.
 * 
 * @return int Quantidade de especialistas disponíveis.
 */
int Board::specialists() {
    return specialists_;
}
