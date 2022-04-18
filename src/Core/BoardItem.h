#ifndef BOARD_ITEM_H
#define BOARD_ITEM_H

/**
 * @file BoardItem.h
 * @author Alyppyo Coutinho
 * @brief Classe que representa um item de tabuleiro, o qual faz parte da representação lógica do tabueleiro.
 * @version 0.1
 * @date 2022-04-18
 */

/**
 * @brief Possíveis conteúdos para o item.
 */
namespace ItemContent {
    const char Bomb = '*';
    const char NotSelected = '#';
    const char Empty = ' ';
};

/**
 * @brief Possíveis estados para o item.
 */
enum class ItemState {
    NotSelected, Selected, Flagged
};

/**
 * @brief Classe que representa um item de tabuleiro.
 */
class BoardItem {
    char content_;
    ItemState state_;

public:
    BoardItem();

    char content() const;
    ItemState state() const;
    bool isBomb();
    void setContent(char content);
    void setState(ItemState state);
};

#endif