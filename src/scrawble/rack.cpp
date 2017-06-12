#include <scrawble/game_logic.h>
#include <scrawble/rack.h>
#include <stdexcept>

namespace scrawble
{
    tile rack::operator[](size_t index) const
    {
        return at(index);
    }

    tile rack::at(size_t index) const
    {
        if (index < size) {
            return values_[index];
        }
        throw std::out_of_range("invalid index for rack");
    }
    rack& rack::push(const tile& value)
    {
        for (int i = 0; i < size; i++) {
            if (values_[i].empty()) {
                values_[i] = value;
                return *this;
            }
        }
        throw std::out_of_range("no more room in rack push");
    }
    rack& rack::set(size_t index, const tile& value)
    {
        if (index >= size) {
            throw std::out_of_range("no more room in rack push");
        }
        values_[index] = value;
        return *this;
    }
    tile rack::pop(size_t index)
    {
        if (index >= size) {
            throw std::out_of_range("invalid index for rack pop");
        }

        tile value = values_[index];
        values_[index] = tile();
        return value;
    }


    rack& rack::clear()
    {
        for (int i = 0; i < rack::size; i++) {
            values_[i] = tile();
        }
        return *this;
    }

    rack& rack::shuffle()
    {
        std::shuffle(begin(), end(), game_logic::random_generator);
        return *this;
    }


    rack& rack::fill(bag& bag)
    {
        for (int i = 0; i < rack::size; i++) {
            if (values_[i].empty()) {
                values_[i] = bag.next();
            }
        }
        return *this;
    }

    rack& rack::pop(const tile& t)
    {
        auto it = std::find(begin(), end(), t);
        if (it != end()) {
            *it = tile();
        }
        return *this;
    }

    tile rack::replace(size_t index, const tile& tile)
    {
        if (index >= rack::size) {
            throw std::out_of_range("invalid index for player replace");
        }

        auto existing = at(index);

        set(index, tile);

        return existing;
    }

    rack& rack::swap(size_t index1, size_t index2)
    {
        if (index1 >= rack::size || index2 >= rack::size) {
            throw std::out_of_range("invalid index to player swap");
        }

        auto tile1 = pop(index1);
        auto tile2 = pop(index2);

        set(index1, tile2);
        set(index2, tile1);
        return *this;
    }

    rack::iterator rack::begin()
    {
        return values_.begin();
    }

    rack::const_iterator rack::begin() const
    {
        return values_.begin();
    }

    rack::iterator rack::end()
    {
        return values_.end();
    }

    rack::const_iterator rack::end() const
    {
        return values_.end();
    }

    std::string rack::to_string() const
    {
        std::string buf;

        for (int i = 0; i < rack::size; i++) {
            if (values_[i].empty()) {
                continue;
            }

            buf += values_[i].letter();
        }

        return buf;
    }
}