#ifndef SCRAWBLE_BAG_H
#define SCRAWBLE_BAG_H

#include <scrawble/tile.h>
#include <vector>

namespace scrawble
{
    class bag
    {
       public:
        typedef std::vector<tile> list_type;

        class generator_type
        {
           public:
            virtual int next(const list_type &letters) = 0;
        };

        bag(const std::shared_ptr<generator_type> &generator = default_generator());

        bag &push(const tile &tile);

        tile next();

        bool empty() const;

       private:
        static std::shared_ptr<generator_type> default_generator();

        list_type letters_;
        std::shared_ptr<generator_type> generator_;
    };
}

#endif
