#ifndef SCRAWBLE_MOVE_H
#define SCRAWBLE_MOVE_H

#include <scrawble/tile.h>

namespace scrawble {
    class Move {
       public:
        Move(int x, int y, const Tile &tile) : x_(x), y_(y), tile_(tile) {
        }

       private:
        int x_;
        int y_;
        Tile tile_;
    };
}  // namespace scrawble

#endif
