#ifndef SCRAWBLE_BAG_H
#define SCRAWBLE_BAG_H

#include <random>

class bag
{
   public:
    bag &push(char ch)
    {
        letters_.push_back(ch);
        return *this;
    }

    bag &fill(const std::vector<char> &rack, int number = 7)
    {
        while (rack.size() < number) {
            rack.push_back(next());
        }
        return *this;
    }

    char next()
    {
        if (letters_.empty()) {
            throw - 1;
        }
        std::uniform_int_distribution<> dis(0, letters_.size());
        int index = dis(rand_);
        auto it = letters_.begin() + index;
        char value = *it;
        letters_.erase(it);
        return value;
    }

   private:
    std::vector<char> letters_;
    std::default_random_engine rand_;
};

#endif
