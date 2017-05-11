#include <scrawble/bag.h>

namespace scrawble
{
    bag &bag::push(const tile &tile)
    {
        letters_.push_back(tile);
        return *this;
    }

    tile bag::next()
    {
        if (letters_.empty()) {
            throw - 1;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, letters_.size());
        int index = dis(gen);
        auto it = letters_.begin() + index;
        auto value = *it;
        letters_.erase(it);
        return value;
    }
}
