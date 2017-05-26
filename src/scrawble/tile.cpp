#include <scrawble/lexicon/node.h>
#include <scrawble/tile.h>

namespace scrawble
{
    tile::tile() : score_(0), letter_(lexicon::node::EMPTY)
    {
    }

    tile::tile(const char &letter, int score) : score_(score), letter_(letter)
    {
    }

    bool tile::empty() const
    {
        return letter_ == lexicon::node::EMPTY;
    }

    int tile::score() const
    {
        return score_;
    }

    char tile::letter() const
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

    bool tile::operator<(const char &letter) const
    {
        return letter_ < letter;
    }

    bool tile::operator==(const char &letter) const
    {
        return letter_ == letter;
    }
}