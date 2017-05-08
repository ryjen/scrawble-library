#include "player.h"
#include <scrawble/vt100.h>
#include <iostream>

void player::print(std::ostream& out) {
    out << "                ╭───┬───┬───┬───┬───┬───┬───╮\n";
    out << "                ";

    for (auto tile : rack_) {
        out << "│ " << vt100::color(vt100::WHITE, vt100::BRIGHT)
            << tile.letter() << vt100::reset() << " ";
    }
    out << "│\n";

    out << "                ╰───┴───┴───┴───┴───┴───┴───╯\n";
}

player& player::push(const tile& tile) {
    if (rack_.size() < rack_size) {
        rack_.push_back(tile);
    }
    return *this;
}

player& player::pop(const tile& tile) {
    auto it = std::find(rack_.begin(), rack_.end(), tile);
    if (it != rack_.end()) {
        rack_.erase(it);
    }
    return *this;
}