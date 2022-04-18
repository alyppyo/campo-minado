#ifndef BOARD_ITEM_H
#define BOARD_ITEM_H

#include <ostream>

namespace ItemContent {
    const char Bomb = '*';
    const char NotSelected = '#';
    const char Empty = ' ';
};

enum class ItemState {
    NotSelected, Selected, Flagged
};

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