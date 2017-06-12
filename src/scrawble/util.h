#ifndef SCRAWBLE_UTIL_H
#define SCRAWBLE_UTIL_H

#include <functional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace scrawble
{
    /**
     * maps a vector of values to a vector of different values
     * @param values the values to map
     * @param callback the callback to perform individual conversions
     * @return a vector of mapped values
     */
    template <typename P1, typename P2>
    std::vector<P2> map(const std::vector<P1> &values, const std::function<P2(const P1 &)> &callback)
    {
        std::vector<P2> result(values.size());
        for (const P1 &value : values) {
            result.push_back(callback(value));
        }
        return result;
    }

    template <typename P1, typename P2>
    std::set<P2> map(const std::set<P1> &values, const std::function<P2(const P1 &)> &callback)
    {
        std::set<P2> result;
        for (const P1 &value : values) {
            result.insert(callback(value));
        }
        return result;
    }

    /**
     * a pair of items in a zipped value
     */
    template <typename P1, typename P2>
    using zip_item = std::pair<P1, P2>;

    /**
     * a return type for zipping values
     */
    template <typename P1, typename P2>
    using zip_type = std::vector<zip_item<P1, P2>>;

    /**
     * zips the combination of each item at an index in two arrays as a pair in a new array
     * @param v1 a vector of values
     * @param v2 a second vector of values
     * @return a vector of pairs from each parameters
     */
    template <typename P1, typename P2>
    zip_type<P1, P2> zip(const std::vector<P1> &v1, const std::vector<P2> &v2)
    {
        std::vector<std::pair<P1, P2>> result(v1.size());

        auto it = v2.begin();

        for (const P1 &value : v1) {
            if (it == v2.end()) {
                result.emplace_back(value, P2());
            } else {
                result.emplace_back(value, *it++);
            }
        }

        return result;
    }

    /**
     * reduces a vector by accumulation into a new value
     * @param initial the starting value for accumulation
     * @param values the values to reduce to a single value
     * @param accumulator the callback to perform the accumulation
     * @return the reduced value
     */
    template <typename P1, typename P2>
    P1 reduce(P1 &initial, const std::vector<P2> &values, const std::function<P1(P1 &, const P2 &)> &accumulator)
    {
        auto it = values.begin();
        
        if (it == values.end()) {
            return initial;
        }
        
        P1 current = accumulator(initial, *it);

        while(++it != values.end()) {
            current = accumulator(current, *it);
        }

        return current;
    }

    template <typename P1>
    std::string join(const std::vector<P1> &value, const std::string &delimiter)
    {
        std::ostringstream buf;

        std::copy(value.begin(), value.end(), std::ostream_iterator<P1>(buf, delimiter.c_str()));

        return buf.str();
    }

    template <typename P1>
    std::vector<P1> select(const std::vector<P1> &values, const std::function<bool(const P1 &)> &callback)
    {
        std::vector<P1> result;

        for (const P1 &value : values) {
            if (callback(value)) {
                result.push_back(value);
            }
        }
        return result;
    }
    
    
    template<typename P1>
    using split_type = std::pair<P1, P1>;
    
    template<typename P1>
    split_type<std::vector<P1>> split(const std::vector<P1> &values, int count)
    {
        assert(values.size() >= count);
        
        std::vector<P1> v1(values.begin(), values.begin() + count);
        
        std::vector<P1> v2(values.begin() + count, values.end());
        
        return {v1, v2};
    }
}

#endif
