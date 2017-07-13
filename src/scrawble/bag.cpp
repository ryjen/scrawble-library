#include <scrawble/bag.h>
#include <scrawble/game_logic.h>
#include <memory>
#include <stdexcept>

namespace scrawble
{
    Bag &Bag::push(const Tile::Ptr &tile)
    {
        letters_.push_back(tile);
        return *this;
    }

    Bag &Bag::push(const Tile::Type &letter, int score)
    {
        letters_.emplace_back(std::make_shared<Tile>(letter, score));
        return *this;
    }

    bool Bag::empty() const
    {
        return letters_.empty();
    }

    Tile::Ptr Bag::next()
    {
        if (letters_.empty()) {
            throw std::out_of_range("No more letters");
        }

        std::uniform_int_distribution<> dis(0, letters_.size() - 1);

        auto index = dis(GameLogic::random_generator);

        if (index < 0 || index >= letters_.size()) {
            throw std::out_of_range("invalid generated index");
        }

        auto it = letters_.begin() + index;

        auto value = *it;

        letters_.erase(it);

        return value;
    }

    Tile::Ptr Bag::next(char letter)
    {
        if (letters_.empty()) {
            throw std::out_of_range("No more letters");
        }

        auto it = std::find_if(std::begin(letters_), std::end(letters_),
                               [&letter](const Tile::Ptr &tile) { return tile->letter() == letter; });

        if (it == std::end(letters_)) {
            throw std::out_of_range("invalid generated index");
        }

        auto value = *it;

        letters_.erase(it);

        return value;
    }
}
