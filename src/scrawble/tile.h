#ifndef SCRAWBLE_TILE_H
#define SCRAWBLE_TILE_H

#include <string>

namespace scrawble
{
    class tile
    {
       public:
        tile(const char &letter, int score) : score_(score), letter_(letter)
        {
        }

        int score() const
        {
            return score_;
        }

        char letter() const
        {
            return letter_;
        }

        bool operator<(const tile &other) const
        {
            return letter_ < other.letter_;
        }
        bool operator==(const tile &other) const
        {
            return letter_ == other.letter_;
        }

        bool operator<(const char &letter) const
        {
            return letter_ < letter;
        }

        bool operator==(const char &letter) const
        {
            return letter_ == letter;
        }

       private:
        int score_;
        char letter_;
    };
}

#endif
