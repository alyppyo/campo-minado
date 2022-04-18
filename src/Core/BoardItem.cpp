#include "BoardItem.h"

BoardItem::BoardItem() :
    content_(ItemContent::Empty), state_(ItemState::NotSelected) {}

char BoardItem::content() const {
    return content_;
}

ItemState BoardItem::state() const {
    return state_;
}

bool BoardItem::isBomb() {
    return content_ == ItemContent::Bomb;
}

void BoardItem::setContent(char content) {
    content_ = content;
}

void BoardItem::setState(ItemState state) {
    state_ = state;
}

std::ostream& operator<<(std::ostream& out, const BoardItem& item) {
    out << static_cast<char>(item.content());
    return out;
}