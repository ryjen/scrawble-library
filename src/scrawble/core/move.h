#ifndef SCRAWBLE_MOVE_H
#define SCRAWBLE_MOVE_H

#include <scrawble/tile.h>

namespace scrawble
{
    class Move
    {
       public:
        Move(int x, int y, const Tile::Ptr &tile) : x_(x), y_(y), tile_(tile)
        {
        }

        int score() const
        {
            return tile_ == nullptr ? 0 : tile_->score();
        }

        Tile::Type letter() const
        {
            return tile_ == nullptr ? 0 : tile_->letter();
        }

        int x() const
        {
            return x_;
        }

        int y() const
        {
            return y_;
        }

       private:
        int x_;
        int y_;
        Tile::Ptr tile_;
    };
}

#endif
