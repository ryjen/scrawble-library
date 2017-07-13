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
        typedef std::vector<Tile::Ptr> List;

        Bag &push(const Tile::Ptr &tile);

        Bag &push(const Tile::Type &letter, int score);

        Tile::Ptr next();

        bool empty() const;

        Tile::Ptr next(char letter);

       private:
        List letters_;
    };
}

#endif
