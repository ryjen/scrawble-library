#ifndef SCRAWBLE_RACK_H
#define SCRAWBLE_RACK_H

#include <scrawble/tile.h>
#include <array>
#include <stdexcept>

namespace scrawble
{
    class rack
    {
       public:
        static const int size = 7;
        typedef std::array<tile, size>::iterator iterator;
        typedef std::array<tile, size>::const_iterator const_iterator;

        tile operator[](size_t index) const
        {
            if (index < size) {
                return values_[index];
            }
            throw std::out_of_range("invalid index for rack");
        }

        rack &push(const tile &value)
        {
            for (int i = 0; i < size; i++) {
                if (values_[i].empty()) {
                    values_[i] = value;
                    return *this;
                }
            }
            throw std::out_of_range("no more room in rack push");
        }

        tile pop(size_t index)
        {
            if (index >= size) {
                throw std::out_of_range("invalid index for rack pop");
            }

            tile value = values_[index];
            values_[index] = tile();
            return value;
        }

        iterator begin()
        {
            return values_.begin();
        }

        const_iterator begin() const
        {
            return values_.begin();
        }

        iterator end()
        {
            return values_.end();
        }

        const_iterator end() const
        {
            return values_.end();
        }

       private:
        std::array<tile, size> values_;
    };
}

#endif
