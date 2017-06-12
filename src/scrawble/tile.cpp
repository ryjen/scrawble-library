
#include <scrawble/tile.h>

namespace scrawble
{
    const char tile::EMPTY = ' ';

    tile::tile() : score_(0), letter_(EMPTY)
    {
    }

    tile::tile(const value_type &letter, int score) : score_(score), letter_(letter)
    {
    }

    bool tile::empty() const
    {
        return letter_ == EMPTY;
    }

    int tile::score() const
    {
        return score_;
    }

    tile::value_type tile::letter() const
    {
        return letter_;
    }

    bool tile::operator<(const tile &other) const
    {
        return letter_ < other.letter_;
    }
    bool tile::operator==(const tile &other) const
    {
        return letter_ == other.letter_;
    }

    bool tile::operator<(const value_type &letter) const
    {
        return letter_ < letter;
    }

    bool tile::operator==(const value_type &letter) const
    {
        return letter_ == letter;
    }
}