#ifndef SCRAWBLE_RACK_H
#define SCRAWBLE_RACK_H

#include <scrawble/bag.h>
#include <scrawble/tile.h>
#include <array>

namespace scrawble
{
    class rack
    {
       public:
        static const int size = 7;
        typedef std::array<tile, size>::iterator iterator;
        typedef std::array<tile, size>::const_iterator const_iterator;

        tile operator[](size_t index) const;

        tile at(size_t index) const;
        rack& push(const tile& value);
        rack& set(size_t index, const tile& value);
        tile pop(size_t index);
        rack& clear();
        rack& shuffle();
        rack& fill(bag& bag);
        rack& pop(const tile& t);
        tile replace(size_t index, const tile& tile);
        rack& swap(size_t index1, size_t index2);
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        std::string to_string() const;

       private:
        std::array<tile, size> values_;
    };
}

#endif
