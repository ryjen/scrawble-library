#ifndef SCRAWBLE_BAG_H
#define SCRAWBLE_BAG_H

#include <scrawble/tile.h>
#include <memory>
#include <vector>

namespace scrawble
{
    class bag
    {
       public:
        typedef std::vector<tile> list_type;

        bag &push(const tile &tile);

        tile next();

        bool empty() const;

        tile next(char letter);

       private:
        list_type letters_;
    };
}

#endif
