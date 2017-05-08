#include <scrawble/bag.h>

bag::bag(const config &conf)
{
    for (auto tile : conf.letters()) {
        for (int i = 0; i < tile.count; i++) {
            letters_.emplace_back(tile.letter, tile.score);
        }
    }
}

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
    std::uniform_int_distribution<> dis(0, letters_.size());
    int index = dis(rand_);
    auto it = letters_.begin() + index;
    auto value = *it;
    letters_.erase(it);
    return value;
}