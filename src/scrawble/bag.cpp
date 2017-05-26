#include <scrawble/bag.h>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <memory>

namespace scrawble
{
    namespace detail
    {
        class default_randomizer : public bag::randomizer
        {
           public:
            int next_index(const bag::list_type &values)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, values.size());
                return dis(gen);
            }
        };
    }

    std::shared_ptr<bag::randomizer> bag::default_randomizer()
    {
        return std::make_shared<detail::default_randomizer>();
    }

    bag::bag(const std::shared_ptr<randomizer> &randomizer) : randomizer_(randomizer)
    {
    }

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

        auto index = randomizer_->next_index(letters_);

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
