#include <scrawble/arc.h>
#include <scrawble/node.h>
#include <scrawble/path.h>
#include <scrawble/util.h>
#include <algorithm>
#include <cassert>
#include <memory>

namespace scrawble
{
    node::node() : arcs_()
    {
    }

    node::node(const node &other) : arcs_(other.arcs_)
    {
    }

    node::node(node &&other) : arcs_(std::move(other.arcs_))
    {
    }

    node::~node()
    {
    }

    node &node::operator=(const node &other)
    {
        arcs_ = other.arcs_;
        return *this;
    }

    node &node::operator=(node &&other)
    {
        arcs_ = std::move(other.arcs_);
        return *this;
    }

    bool node::operator==(const node &other) const
    {
        return std::equal(arcs_.begin(), arcs_.end(), other.arcs_.begin());
    }

    node::arc_ptr node::create_arc(const value_type &value, const destination_type &destination)
    {
        auto it = arcs_.find(value);

        if (it != arcs_.end()) {
            return it->second;
        }

        arc_ptr arc = std::make_shared<scrawble::arc>(destination ? destination : std::make_shared<node>());

        arcs_.emplace(value, arc);

        return arc;
    }

    bool node::is_arc(const value_type &value) const
    {
        return arcs_.count(value) > 0;
    }

    node::arc_ptr node::create_final_arc(const value_type &value, const value_type &final,
                                         const destination_type &destination)
    {
        auto arc = create_arc(value, destination);

        arc->push_final_value(final);

        return arc;
    }

    node::destination_type node::create_path(const value_list &values, const destination_list &destinations)
    {
        auto zipped = zip(values, destinations);

        reduce_callback<destination_type, zip_item<value_type, destination_type>> callback =
            [](const destination_type &memo, const zip_item<value_type, destination_type> &value) -> destination_type {
            return memo->create_arc(value.first, value.second)->destination();
        };

        return reduce(shared_from_this(), zipped, callback);
    }

    bool node::is_path(const value_list &values) const
    {
        if (values.empty()) {
            return true;
        }

        auto first = values.begin();

        if (!is_arc(*first)) {
            return false;
        }

        return follow_arc(*first)->is_path({values.back()});
    }

    std::tuple<node::value_list, node::value_type, node::value_type> node::chop_last_pair(const value_list &values)
    {
        auto it = values.rbegin();

        if (it == values.rend()) {
            return std::make_tuple(value_list(values.begin(), it.base()), value_type(), value_type());
        }

        auto last_value = *it++;

        if (it == values.rend()) {
            return std::make_tuple(value_list(values.begin(), it.base()), value_type(), last_value);
        }

        auto second_last = *it++;

        return std::make_tuple(value_list(values.begin(), it.base()), second_last, last_value);
    }

    node::destination_type node::create_final_path(const value_list &values, const destination_list &destinations)
    {
        auto tuple = chop_last_pair(values);

        auto remaining = std::get<0>(tuple);

        auto second_last_node = create_path(remaining, destinations);

        destination_type final_destination;

        if (remaining.size() < destinations.size()) {
            final_destination = destinations[remaining.size()];
        }

        second_last_node->create_final_arc(std::get<1>(tuple), std::get<2>(tuple), final_destination);

        return second_last_node;
    }

    bool node::is_final_path(const value_list &values) const
    {
        auto tuple = chop_last_pair(values);

        auto remaining = std::get<0>(tuple);

        if (!is_path(remaining)) {
            return false;
        }

        path_ptr final_path(new path({std::get<1>(tuple), std::get<2>(tuple)}));

        auto final_paths = follow_path(remaining)->final_paths();

        return std::find(final_paths.begin(), final_paths.end(), final_path) != final_paths.end();
    }

    const node::ptr &node::follow_arc(const value_type &value) const
    {
        auto it = arcs_.find(value);

        if (it == arcs_.end()) {
            throw std::out_of_range("value not found");
        }

        return it->second->destination();
    }

    const node::ptr &node::follow_path(const value_list &values) const
    {
        if (values.empty()) {
            throw std::invalid_argument("empty values");
        }
        return follow_arc(values.front())->follow_path({values.back()});
    }

    std::vector<path::ptr> node::final_paths() const
    {
        std::vector<path::ptr> result;

        for (auto &pair : arcs_) {
            value_list path;
            path.push_back(pair.first);
            for (auto &p1 : pair.second->final_paths()) {
                for (auto &p2 : p1->to_array()) {
                    path.push_back(p2);
                }
            }
            result.push_back(std::make_shared<scrawble::path>(path));
        }
        return result;
    }
}
