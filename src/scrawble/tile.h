#ifndef SCRAWBLE_TILE_H
#define SCRAWBLE_TILE_H

#include <string>

namespace scrawble
{
    class tile
    {
       public:
        static const char EMPTY = '_';
        static const char DIRSYM = '>';

        tile(const std::string &letter, int score) : score_(score), letter_(letter)
        {
        }

        int score() const
        {
            return score_;
        }

        std::string letter() const
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

       private:
        int score_;
        std::string letter_;
    };
}

#endif
