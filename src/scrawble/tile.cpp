
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

    Tile::Tile(const Type &letter, int score) : score_(score), letter_(letter)
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