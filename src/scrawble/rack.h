#ifndef SCRAWBLE_RACK_H
#define SCRAWBLE_RACK_H

#include <scrawble/tile.h>
#include <stdexcept>

namespace scrawble
{
    class rack
    {
       public:
        static const int size = 7;

        tile &operator[](size_t index) const
        {
            if (index < size) {
                return values_[index];
            }
            throw std::out_of_range("invalid index for rack");
        }

        rack &push(const tile &value)
        {
            for (int i = 0; i < size; i++) {
                if (!values_[i]) {
                    values_[i] = value;
                    return *this;
                }
            }
            throw std::out_of_range("no more room in rack push");
        }

        tile &pop(size_t index)
        {
            if (index >= size) {
                throw std::out_of_range("invalid index for rack pop");
            }

            tile &value = values_[index];
            values_[index] = nullptr;
            return value;
        }

       private:
        std::array<tile, size> values_;
    };
}

#endif
