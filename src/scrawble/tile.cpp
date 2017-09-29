
#include <scrawble/tile.h>

namespace scrawble
{
    BlankTile::BlankTile() : Tile()
    {
    }

    BlankTile::BlankTile(const Type &letter) : Tile(letter, 0)
    {
    }

    bool BlankTile::blank() const
    {
        return true;
    }

    Tile::Tile() : score_(0), letter_(0)
    {
    }

    Tile::Tile(const Type &letter, int score) : score_(score), letter_(tolower(letter))
    {
    }

    bool Tile::blank() const
    {
        return false;
    }

    int Tile::score() const
    {
        return score_;
    }

    Tile::Type Tile::letter() const
    {
        return letter_;
    }

    Tile &Tile::letter(const Type &value)
    {
        letter_ = value;
        return *this;
    }

    bool Tile::operator<(const Tile &other) const
    {
        return letter_ < other.letter_;
    }
    bool Tile::operator==(const Tile &other) const
    {
        return letter_ == other.letter_;
    }

    bool Tile::operator<(const Type &letter) const
    {
        return letter_ < letter;
    }

    bool Tile::operator==(const Type &letter) const
    {
        return letter_ == letter;
    }
}  // namespace scrawble