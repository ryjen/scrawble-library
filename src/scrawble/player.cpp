#include <scrawble/player.h>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>

namespace scrawble
{
    player& player::push(const tile& tile)
    {
        if (rack_.size() < rack_size) {
            rack_.push_back(tile);
        }
        return *this;
    }

    player& player::pop(const tile& tile)
    {
        auto it = std::find(rack_.begin(), rack_.end(), tile);
        if (it != rack_.end()) {
            rack_.erase(it);
        }
        return *this;
    }

    player& player::clear()
    {
        rack_.clear();
        return *this;
    }

    player& player::shuffle()
    {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(rack_.begin(), rack_.end(), g);
        return *this;
    }

    const std::vector<tile>& player::rack() const
    {
        return rack_;
    }
}
