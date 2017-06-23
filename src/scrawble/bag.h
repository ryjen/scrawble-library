#ifndef SCRAWBLE_BAG_H
#define SCRAWBLE_BAG_H

#include <scrawble/tile.h>
#include <memory>
#include <vector>

namespace scrawble
{
    class Bag
    {
       public:
        typedef std::vector<Tile> list_type;

        Bag &push(const Tile &tile);

        Bag &push(const Tile::value_type &letter, int score);

        Tile next();

        bool empty() const;

        Tile next(char letter);

       private:
        list_type letters_;
    };
}

#endif
