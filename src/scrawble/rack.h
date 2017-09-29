#ifndef SCRAWBLE_RACK_H
#define SCRAWBLE_RACK_H

#include <scrawble/bag.h>
#include <scrawble/tile.h>
#include <array>

namespace scrawble
{
    class Rack
    {
       public:
        static const int size = 7;
        typedef std::array<Tile::Ptr, size>::iterator iterator;
        typedef std::array<Tile::Ptr, size>::const_iterator const_iterator;

        Tile::Ptr operator[](size_t index) const;

        Tile::Ptr at(size_t index) const;
        Rack& push(const Tile::Ptr& value);
        Rack& set(size_t index, const Tile::Ptr& value);
        Tile::Ptr pop(size_t index);
        Tile::Ptr pop();
        int count() const;
        Rack& clear();
        Rack& shuffle();
        Rack& fill(Bag& bag);
        bool empty() const;
        Rack& pop(const Tile::Ptr& t);
        Tile::Ptr replace(size_t index, const Tile::Ptr& tile);
        Rack& swap(size_t index1, size_t index2);
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        std::string to_string() const;

       private:
        Tile::Ptr shift(size_t index);
        std::array<Tile::Ptr, size> values_;
    };
}  // namespace scrawble

#endif
