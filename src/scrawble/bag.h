#ifndef SCRAWBLE_BAG_H
#define SCRAWBLE_BAG_H

#include <scrawble/tile.h>
#include <vector>
#include <memory>

namespace scrawble
{
    class bag
    {
       public:
        typedef std::vector<tile> list_type;

        class randomizer
        {
           public:
            virtual int next_index(const list_type &values) = 0;
        };

        bag(const std::shared_ptr<randomizer> &randomizer = default_randomizer());

        bag &push(const tile &tile);

        tile next();

        bool empty() const;

        tile next(char letter);

       private:
        static std::shared_ptr<randomizer> default_randomizer();

        list_type letters_;
        std::shared_ptr<randomizer> randomizer_;
    };
}

#endif
