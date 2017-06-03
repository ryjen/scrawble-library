#include <scrawble/bag.h>
#include <scrawble/game_logic.h>
#include <memory>
#include <stdexcept>

namespace scrawble
{
    bag &bag::push(const tile &tile)
    {
        letters_.push_back(tile);
        return *this;
    }

    bool bag::empty() const
    {
        return letters_.empty();
    }

    tile bag::next()
    {
        if (letters_.empty()) {
            throw std::out_of_range("No more letters");
        }

        std::uniform_int_distribution<> dis(0, letters_.size() - 1);

        auto index = dis(game_logic::random_generator);

        if (index < 0 || index >= letters_.size()) {
            throw std::out_of_range("invalid generated index");
        }

        auto it = letters_.begin() + index;
        auto value = *it;
        letters_.erase(it);
        return value;
    }

    tile bag::next(char letter)
    {
        if (letters_.empty()) {
            throw std::out_of_range("No more letters");
        }

        auto it = std::find(std::begin(letters_), std::end(letters_), letter);

        if (it == std::end(letters_)) {
            throw std::out_of_range("invalid generated index");
        }
        auto value = *it;
        letters_.erase(it);
        return value;
    }
}
