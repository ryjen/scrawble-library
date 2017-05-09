#ifndef SCRAWBLE_BAG_H
#define SCRAWBLE_BAG_H

#include <scrawble/config.h>
#include <scrawble/tile.h>
#include <random>

class bag
{
   public:
    void init(const config &conf);

    bag &push(const tile &tile);

    tile next();

   private:
    std::vector<tile> letters_;
};

#endif
