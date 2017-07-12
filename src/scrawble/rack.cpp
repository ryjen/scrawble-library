#include <scrawble/game_logic.h>
#include <scrawble/rack.h>
#include <stdexcept>

namespace scrawble {
    Tile Rack::operator[](size_t index) const {
        return at(index);
    }

    Tile Rack::at(size_t index) const {
        if (index < size) {
            return values_[index];
        }
        throw std::out_of_range("invalid index for rack");
    }
    Rack& Rack::push(const Tile& value) {
        for (int i = 0; i < size; i++) {
            if (values_[i].empty()) {
                values_[i] = value;
                return *this;
            }
        }
        throw std::out_of_range("no more room in rack push");
    }
    Rack& Rack::set(size_t index, const Tile& value) {
        if (index >= size) {
            throw std::out_of_range("no more room in rack push");
        }
        values_[index] = value;
        return *this;
    }
    Tile Rack::pop(size_t index) {
        if (index >= size) {
            throw std::out_of_range("invalid index for rack pop");
        }

        Tile value = values_[index];
        values_[index] = Tile();
        return value;
    }

    Rack& Rack::clear() {
        for (int i = 0; i < Rack::size; i++) {
            values_[i] = Tile();
        }
        return *this;
    }

    bool Rack::empty() const {
        for (int i = 0; i < Rack::size; i++) {
            if (!values_[i].empty()) {
                return false;
            }
        }
        return true;
    }

    Rack& Rack::shuffle() {
        std::shuffle(begin(), end(), GameLogic::random_generator);
        return *this;
    }

    Rack& Rack::fill(Bag& bag) {
        for (int i = 0; i < Rack::size; i++) {
            if (values_[i].empty()) {
                values_[i] = bag.next();
            }
        }
        return *this;
    }

    Rack& Rack::pop(const Tile& t) {
        auto it = std::find(begin(), end(), t);
        if (it != end()) {
            *it = Tile();
        }
        return *this;
    }

    Tile Rack::replace(size_t index, const Tile& tile) {
        if (index >= Rack::size) {
            throw std::out_of_range("invalid index for player replace");
        }

        auto existing = at(index);

        set(index, tile);

        return existing;
    }

    Rack& Rack::swap(size_t index1, size_t index2) {
        if (index1 >= Rack::size || index2 >= Rack::size) {
            throw std::out_of_range("invalid index to player swap");
        }

        auto tile1 = pop(index1);
        auto tile2 = pop(index2);

        set(index1, tile2);
        set(index2, tile1);
        return *this;
    }

    Rack::iterator Rack::begin() {
        return values_.begin();
    }

    Rack::const_iterator Rack::begin() const {
        return values_.begin();
    }

    Rack::iterator Rack::end() {
        return values_.end();
    }

    Rack::const_iterator Rack::end() const {
        return values_.end();
    }

    std::string Rack::to_string() const {
        std::string buf;

        for (int i = 0; i < Rack::size; i++) {
            if (values_[i].empty()) {
                continue;
            }

            buf += values_[i].letter();
        }

        return buf;
    }
}  // namespace scrawble