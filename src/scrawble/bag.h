#ifndef SCRAWBLE_BAG_H
#define SCRAWBLE_BAG_H

#include <scrawble/tile.h>
#include <random>

namespace scrawble
{
    class bag
    {
       public:
        bag &push(const tile &tile);

        tile next();

       private:
        std::vector<tile> letters_;
    };
}

#endif
