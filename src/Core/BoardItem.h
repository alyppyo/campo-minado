#ifndef BOARD_ITEM_H
#define BOARD_ITEM_H

#include <ostream>

namespace ItemContent {
    const char Flag = 'B';
    const char Bomb = '*';
    const char QuestionMark = '?';
    const char NotSelected = '#';
    const char Empty = ' ';
};

enum class ItemState {
    NotSelected, Selected, Flagged, QuestionMarked
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

    friend std::ostream& operator<<(std::ostream& out, const BoardItem& item);
};

#endif