#include <scrawble/game_logic.h>
#include <scrawble/rack.h>
#include <cassert>
#include <stdexcept>

namespace scrawble
{
    Tile::Ptr Rack::operator[](size_t index) const
    {
        return at(index);
    }

    Tile::Ptr Rack::at(size_t index) const
    {
        if (index < size) {
            return values_[index];
        }
        throw std::out_of_range("invalid index for rack");
    }
    Rack& Rack::push(const Tile::Ptr& value)
    {
        for (int i = 0; i < size; i++) {
            if (values_[i] == nullptr) {
                values_[i] = value;
                return *this;
            }
        }
        throw std::out_of_range("no more room in rack push");
    }
    Rack& Rack::set(size_t index, const Tile::Ptr& value)
    {
        if (index >= size) {
            throw std::out_of_range("no more room in rack push");
        }
        values_[index] = value;
        return *this;
    }
    Tile::Ptr Rack::pop()
    {
        for (int i = 0; i < size; i++) {
            if (values_[i]) {
                return shift(i);
            }
        }
        throw std::out_of_range("no more tiles in rack");
    }

    Tile::Ptr Rack::shift(size_t index)
    {
        assert(index < size);
        auto value = values_[index];
        for (size_t i = index; i < size - 1; i++) {
            values_[i] = values_[i + 1];
            values_[i + 1] = nullptr;
        }
        return value;
    }

    int Rack::count() const
    {
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (values_[i]) {
                count++;
            }
        }
        return count;
    }

    Tile::Ptr Rack::pop(size_t index)
    {
        if (index >= size) {
            throw std::out_of_range("invalid index for rack pop");
        }

        return shift(index);
    }

    Rack& Rack::clear()
    {
        for (int i = 0; i < Rack::size; i++) {
            values_[i] = nullptr;
        }
        return *this;
    }

    bool Rack::empty() const
    {
        for (int i = 0; i < Rack::size; i++) {
            if (values_[i]) {
                return false;
            }
        }
        return true;
    }

    Rack& Rack::shuffle()
    {
        std::shuffle(begin(), end(), GameLogic::random_generator);
        return *this;
    }

    Rack& Rack::fill(Bag& bag)
    {
        for (int i = 0; i < Rack::size; i++) {
            if (values_[i] == nullptr) {
                values_[i] = bag.next();
            }
        }
        return *this;
    }

    Rack& Rack::pop(const Tile::Ptr& t)
    {
        for (int i = 0; i < size; i++) {
            if (values_[i] == t) {
                values_[i] = nullptr;
                break;
            }
        }
        return *this;
    }

    Tile::Ptr Rack::replace(size_t index, const Tile::Ptr& tile)
    {
        if (index >= Rack::size) {
            throw std::out_of_range("invalid index for player replace");
        }

        auto existing = at(index);

        set(index, tile);

        return existing;
    }

    Rack& Rack::swap(size_t index1, size_t index2)
    {
        if (index1 >= Rack::size || index2 >= Rack::size) {
            throw std::out_of_range("invalid index to player swap");
        }

        auto tile1 = pop(index1);
        auto tile2 = pop(index2);

        set(index1, tile2);
        set(index2, tile1);
        return *this;
    }

    Rack::iterator Rack::begin()
    {
        return values_.begin();
    }

    Rack::const_iterator Rack::begin() const
    {
        return values_.begin();
    }

    Rack::iterator Rack::end()
    {
        return values_.end();
    }

    Rack::const_iterator Rack::end() const
    {
        return values_.end();
    }

    std::string Rack::to_string() const
    {
        std::string buf;

        for (int i = 0; i < Rack::size; i++) {
            if (values_[i] == nullptr) {
                continue;
            }

            buf += values_[i]->letter();
        }

        return buf;
    }
}  // namespace scrawble