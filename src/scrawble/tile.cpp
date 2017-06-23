
#include <scrawble/tile.h>

namespace scrawble
{
    const char Tile::EMPTY = ' ';

    Tile::Tile() : score_(0), letter_(EMPTY)
    {
    }

    Tile::Tile(const value_type &letter, int score) : score_(score), letter_(letter)
    {
    }

    bool Tile::empty() const
    {
        return letter_ == EMPTY;
    }

    int Tile::score() const
    {
        return score_;
    }

    Tile::value_type Tile::letter() const
    {
        return letter_;
    }

    bool Tile::operator<(const Tile &other) const
    {
        return letter_ < other.letter_;
    }
    bool Tile::operator==(const Tile &other) const
    {
        return letter_ == other.letter_;
    }

    bool Tile::operator<(const value_type &letter) const
    {
        return letter_ < letter;
    }

    bool Tile::operator==(const value_type &letter) const
    {
        return letter_ == letter;
    }
}