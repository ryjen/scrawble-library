#include <scrawble/path.h>
#include <scrawble/util.h>
#include <scrawble/word.h>
#include <algorithm>

namespace scrawble
{
    const path::value_type path::DELIMITER = 0x1E;

    bool path::operator==(const path &other) const
    {
        return std::equal(values_.begin(), values_.end(), other.values_.begin());
    }

    bool path::operator<(const path &other) const
    {
        return values_ < other.values_;
    }
    
    path::path(const value_type &value) : values_({value})
    {}

    path::path(const value_list &values) : values_(values)
    {
    }

    path::path(const value_list &values, const path::ptr &other) : values_(values)
    {
        values_.insert(values_.end(), other->values_.begin(), other->values_.end());
    }

    
    path::path(const path &other) : values_(other.values_)
    {}
    
    path::path(path &&other) : values_(std::move(other.values_))
    {}
    
    path::~path() {}
    
    path &path::operator=(const path &other) {
        values_ = other.values_;
        return *this;
    }
    
    path &path::operator=(path &&other) {
        values_ = std::move(other.values_);
        return *this;
    }
    
    path::value_list path::reverse_prefix_values() const
    {
        auto it = std::find(values_.begin(), values_.end(), path::DELIMITER);

        if (it == values_.end()) {
            return values_;
        }

        return value_list(values_.begin(), it);
    }

    path::value_list path::suffix_values() const
    {
        auto it = std::find(values_.rbegin(), values_.rend(), path::DELIMITER);

        if (it == values_.rend() || (it + 1) == values_.rend()) {
            return {};
        }

        return value_list(it, values_.rend());
    }

    bool path::has_delimiter() const
    {
        return std::find(values_.begin(), values_.end(), path::DELIMITER) != values_.end();
    }

    std::string path::to_string() const
    {
        return join(values_, " > ");
    }

    const path::value_list &path::to_array() const
    {
        return values_;
    }

    bool path::starts_with(const value_list &values) const
    {
        auto i1 = values_.begin();
        auto i2 = values.begin();

        while (i1 != values_.end() && i2 != values.end()) {
            if (*i1 != *i2) {
                return false;
            }
            ++i1, ++i2;
        }

        return i2 == values.end();
    }

    word path::to_word() const
    {
        auto prefix = reverse_prefix_values();
        value_list reverted(prefix.rbegin(), prefix.rend());
        auto suffix = suffix_values();
        reverted.insert(reverted.end(), suffix.begin(), suffix.end());
        return word(reverted);
    }
}
