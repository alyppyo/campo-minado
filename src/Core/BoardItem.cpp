/**
 * @file BoardItem.cpp
 * @author Alyppyo Coutinho
 * @brief Implementação dos métodos da classe que representa um item do tabuleiro.
 * @version 0.1
 * @date 2022-04-18
 */

#include "BoardItem.h"

/**
 * @brief Constrói um item do tabuleiro.
 * 
 */
BoardItem::BoardItem() :
    content_(ItemContent::Empty), state_(ItemState::NotSelected) {}

/**
 * @brief Retorna o conteúdo do item.
 * 
 * @return char Conteúdo do item.
 */
char BoardItem::content() const {
    return content_;
}

/**
 * @brief Retorna o estado do item.
 * 
 * @return ItemState Estado do item.
 */
ItemState BoardItem::state() const {
    return state_;
}

/**
 * @brief Indica se o item contém uma bomba.
 * 
 * @return Verdadeiro caso haja uma bomba. Falso, caso contrário.
 */
bool BoardItem::isBomb() {
    return content_ == ItemContent::Bomb;
}

/**
 * @brief Define o conteúdo do item.
 * 
 * @param content Novo conteúdo do item.
 */
void BoardItem::setContent(char content) {
    content_ = content;
}

/**
 * @brief Define o estado do item.
 * 
 * @param state Novo estado do item.
 */
void BoardItem::setState(ItemState state) {
    state_ = state;
}
