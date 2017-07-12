#ifndef SCRAWBLE_TILE_H
#define SCRAWBLE_TILE_H

#include <string>

namespace scrawble {
    class Tile {
       public:
        typedef char value_type;

        static const value_type EMPTY;

        Tile();

        Tile(const value_type &letter, int score);

        bool empty() const;

        virtual bool blank() const;

        int score() const;

        value_type letter() const;

        bool operator<(const Tile &other) const;

        bool operator==(const Tile &other) const;

        bool operator<(const value_type &letter) const;

        bool operator==(const value_type &letter) const;

       private:
        int score_;
        value_type letter_;
    };

    class BlankTile : public Tile {
       public:
        BlankTile();
        BlankTile(const value_type &letter);

        bool blank() const;
    };
}  // namespace scrawble

#endif
