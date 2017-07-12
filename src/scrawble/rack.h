#ifndef SCRAWBLE_RACK_H
#define SCRAWBLE_RACK_H

#include <scrawble/bag.h>
#include <scrawble/tile.h>
#include <array>

namespace scrawble {
    class Rack {
       public:
        static const int size = 7;
        typedef std::array<Tile, size>::iterator iterator;
        typedef std::array<Tile, size>::const_iterator const_iterator;

        Tile operator[](size_t index) const;

        Tile at(size_t index) const;
        Rack& push(const Tile& value);
        Rack& set(size_t index, const Tile& value);
        Tile pop(size_t index);
        Rack& clear();
        Rack& shuffle();
        Rack& fill(Bag& bag);
        bool empty() const;
        Rack& pop(const Tile& t);
        Tile replace(size_t index, const Tile& tile);
        Rack& swap(size_t index1, size_t index2);
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        std::string to_string() const;

       private:
        std::array<Tile, size> values_;
    };
}  // namespace scrawble

#endif
