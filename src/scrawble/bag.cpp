#include <scrawble/bag.h>
#include <random>

namespace scrawble
{
    namespace detail
    {
        class default_generator_type : public bag::generator_type
        {
           public:
            int next(const bag::list_type &letters)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, letters.size());
                return dis(gen);
            }
        };
    }

    std::shared_ptr<bag::generator_type> bag::default_generator()
    {
        return std::make_shared<detail::default_generator_type>();
    }

    bag::bag(const std::shared_ptr<generator_type> &generator) : generator_(generator)
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

        auto index = generator_->next(letters_);

        if (index < 0 || index >= letters_.size()) {
            throw std::out_of_range("invalid generated index");
        }

        auto it = letters_.begin() + index;
        auto value = *it;
        letters_.erase(it);
        return value;
    }
}
