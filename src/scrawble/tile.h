#ifndef SCRAWBLE_TILE_H
#define SCRAWBLE_TILE_H

#include <string>

namespace scrawble
{
    class tile
    {
       public:
        tile();

        tile(const char &letter, int score);

        bool empty() const;

        int score() const;

        char letter() const;

        bool operator<(const tile &other) const;

        bool operator==(const tile &other) const;

        bool operator<(const char &letter) const;

        bool operator==(const char &letter) const;

       private:
        int score_;
        char letter_;
    };
}

#endif
