#ifndef SCRAWBLE_TILE_H
#define SCRAWBLE_TILE_H

#include <string>

namespace scrawble
{
    class Tile
    {
       public:
        typedef char Type;
        typedef std::shared_ptr<Tile> Ptr;

        Tile();

        Tile(const Type &letter, int score);

        virtual bool blank() const;

        int score() const;

        Type letter() const;

        bool operator<(const Tile &other) const;

        bool operator==(const Tile &other) const;

        bool operator<(const Type &letter) const;

        bool operator==(const Type &letter) const;

       private:
        int score_;
        Type letter_;
    };

    class BlankTile : public Tile
    {
       public:
        BlankTile();
        BlankTile(const Type &letter);

        bool blank() const;
    };
}  // namespace scrawble

#endif
