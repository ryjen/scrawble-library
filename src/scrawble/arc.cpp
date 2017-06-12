#include <scrawble/arc.h>
#include <scrawble/path.h>
#include <scrawble/util.h>
#include <scrawble/path.h>
#include <scrawble/node.h>
#include <memory>
#include <algorithm>

namespace scrawble
{
    bool arc::operator==(const arc &value) const
    {
        return std::equal(values_.begin(), values_.end(), value.values_.begin());
    }

    arc::arc(const node_ptr &value) : destination_(value)
    {
    }
    
    arc::arc(const arc &other) : destination_(other.destination_), values_(other.values_)
    {}
    
    arc::arc(arc &&other) : destination_(std::move(other.destination_)), values_(std::move(other.values_))
    {}
    
    arc::~arc() {}
    
    arc &arc::operator=(const arc &other)
    {
        destination_ = other.destination_;
        values_ = other.values_;
        return *this;
    }
    
    arc &arc::operator=(arc &&other)
    {
        destination_ = other.destination_;
        values_ = other.values_;
        return *this;
    }

    arc &arc::push_final_value(const value_type &value)
    {
        values_.insert(value);
        return *this;
    }

    std::set<arc::path_ptr> arc::final_paths() const
    {
        auto result = scrawble::map<value_type, path::ptr>(values_, [](const value_type &value) { return std::make_shared<path>(value); });

        for (auto path : destination_->final_paths()) {
            result.insert(path);
        }

        return result;
    }

    const arc::node_ptr &arc::destination() const
    {
        return destination_;
    }
}
