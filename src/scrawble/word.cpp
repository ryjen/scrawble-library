
#include <scrawble/path.h>
#include <scrawble/word.h>
#include <algorithm>

namespace scrawble
{
    bool word::operator==(const word &value) const
    {
        return std::equal(values_.begin(), values_.end(), value.values_.begin());
    }

    word::word(const value_list &values) : values_(values)
    {
    }

    word::word(const std::string &value) : values_(value.begin(), value.end())
    {
    }

    std::string word::to_string() const
    {
        return std::string(values_.begin(), values_.end());
    }

    std::vector<path> word::delimited_paths() const
    {
        std::vector<path> result;
        for (int index = 1; index < values_.size(); index++) {
            value_list slice(values_.begin(), values_.begin() + index);
            value_list value(slice.rbegin(), slice.rend());
            value.push_back(path::DELIMITER);
            value.insert(value.end(), values_.begin() + index, values_.end());
            result.emplace_back(value);
        }
        return result;
    }
}