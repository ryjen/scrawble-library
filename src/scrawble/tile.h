#ifndef SCRAWBLE_TILE_H
#define SCRAWBLE_TILE_H

#include <string>

namespace scrawble
{
    class tile
    {
       public:
        typedef char value_type;

        static const value_type EMPTY;

        tile();

        tile(const value_type &letter, int score);

        bool empty() const;

        int score() const;

        value_type letter() const;

        bool operator<(const tile &other) const;

        bool operator==(const tile &other) const;

        bool operator<(const value_type &letter) const;

        bool operator==(const value_type &letter) const;

       private:
        int score_;
        value_type letter_;
    };
}

#endif
