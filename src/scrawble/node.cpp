#include <scrawble/arc.h>
#include <scrawble/node.h>
#include <scrawble/path.h>
#include <scrawble/util.h>
#include <algorithm>
#include <cassert>

namespace scrawble
{
    bool node::operator==(const node &other) const
    {
        return std::equal(arcs_.begin(), arcs_.end(), other.arcs_.begin());
    }

    arc node::create_arc(const value_type &value, const node &destination)
    {
        auto it = arcs_.find(value);
        if (it != arcs_.end()) {
            return it->second;
        }

        scrawble::arc arc(destination);

        arcs_.emplace(value, arc);
        return arc;
    }

    bool node::is_arc(const value_type &value) const
    {
        return arcs_.count(value) > 0;
    }

    arc node::create_final_arc(const value_type &value, const value_type &final, const node &destination)
    {
        scrawble::arc arc = create_arc(value, destination);

        arc.push_final_value(final);

        return arc;
    }

    node::destination_type node::create_path(const value_list &values, const destination_list &destinations)
    {
        auto zipped = zip(values, destinations);
        return reduce<destination_type, zip_item<value_type, destination_type>>(
            *this, zipped, [&](destination_type &memo, const zip_item<value_type, destination_type> &value) {
                return memo.create_arc(value.first, value.second).destination();
            });
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

        return follow_arc(*first).is_path({values.back()});
    }

    std::tuple<node::value_list, node::value_type, node::value_type> node::chop_last_pair(const value_list &values)
    {
        assert(values.size() >= 2);
        value_list initial_values(values);

        value_type last_value = initial_values.back();
        initial_values.pop_back();

        value_type second_last_value = initial_values.back();
        initial_values.pop_back();

        return std::make_tuple(initial_values, second_last_value, last_value);
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

        second_last_node.create_final_arc(std::get<1>(tuple), std::get<2>(tuple), final_destination);

        return final_destination;
    }

    bool node::is_final_path(const value_list &values) const
    {
        auto tuple = chop_last_pair(values);

        auto remaining = std::get<0>(tuple);

        if (!is_path(remaining)) {
            return false;
        }

        path final_path({std::get<1>(tuple), std::get<2>(tuple)});

        auto final_paths = follow_path(remaining).final_paths();

        return std::find(final_paths.begin(), final_paths.end(), final_path) != final_paths.end();
    }

    const node &node::follow_arc(const value_type &value) const
    {
        auto it = arcs_.find(value);

        if (it == arcs_.end()) {
            throw std::out_of_range("value not found");
        }

        return it->second.destination();
    }

    const scrawble::node &node::follow_path(const value_list &values) const
    {
        if (values.empty()) {
            return *this;
        }
        return follow_arc(values.front()).follow_path({values.back()});
    }

    std::vector<path> node::final_paths() const
    {
        std::vector<path> result;

        for (auto &pair : arcs_) {
            value_list path;
            path.push_back(pair.first);
            for (auto &p1 : pair.second.final_paths()) {
                for (auto &p2 : p1.to_array()) {
                    path.push_back(p2);
                }
            }
            result.emplace_back(path);
        }
        return result;
    }
}