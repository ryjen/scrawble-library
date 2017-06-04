#include <scrawble/game_logic.h>
#include <scrawble/player.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

namespace scrawble
{
    player& player::push(const tile& tile)
    {
        rack_.push(tile);
        return *this;
    }

    tile player::replace(size_t index, const tile& tile)
    {
        if (index >= rack::size) {
            throw std::out_of_range("invalid index for player replace");
        }

        auto existing = rack_[index];

        rack_.set(index, tile);

        return existing;
    }

    player& player::pop(const tile& t)
    {
        auto it = std::find(rack_.begin(), rack_.end(), t);
        if (it != rack_.end()) {
            *it = tile();
        }
        return *this;
    }

    tile player::pop(size_t index)
    {
        if (index >= rack::size) {
            throw std::out_of_range("invalid index for player pop");
        }
        return rack_.pop(index);
    }

    tile player::get(size_t index)
    {
        if (index >= rack::size) {
            return tile();
        }
        return rack_[index];
    }

    player& player::swap(size_t index1, size_t index2)
    {
        if (index1 >= rack::size || index2 >= rack::size) {
            throw std::out_of_range("invalid index to player swap");
        }

        auto tile1 = rack_.pop(index1);
        auto tile2 = rack_.pop(index2);

        rack_.set(index1, tile2);
        rack_.set(index2, tile1);
        return *this;
    }

    player& player::clear()
    {
        for (int i = 0; i < rack::size; i++) {
            rack_[i] = tile();
        }
        return *this;
    }

    player& player::shuffle()
    {
        std::shuffle(rack_.begin(), rack_.end(), game_logic::random_generator);
        return *this;
    }

    const scrawble::rack& player::rack() const
    {
        return rack_;
    }

    player& player::add_score(int score)
    {
        score_ += score;
        return *this;
    }

    player& player::fill(bag& bag)
    {
        for (int i = 0; i < rack::size; i++) {
            if (rack_[i].empty()) {
                rack_.set(i, bag.next());
            }
        }
        return *this;
    }
}
