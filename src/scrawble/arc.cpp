#include <scrawble/arc.h>
#include <scrawble/path.h>
#include <scrawble/util.h>
#include <algorithm>

namespace scrawble
{
    bool arc::operator==(const arc &value) const
    {
        return std::equal(values_.begin(), values_.end(), value.values_.begin());
    }

    arc::arc(const node &value) : destination_(value)
    {
    }

    arc &arc::push_final_value(const value_type &value)
    {
        values_.insert(value);
        return *this;
    }

    std::set<path> arc::final_paths() const
    {
        auto result = map<value_type, path>(values_, [](const value_type &value) { return path({value}); });

        for (auto path : destination_.final_paths()) {
            result.insert(path);
        }

        return result;
    }

    const node &arc::destination() const
    {
        return destination_;
    }
}