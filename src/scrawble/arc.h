#ifndef SCRAWBLE_ARC_H
#define SCRAWBLE_ARC_H

#include <scrawble/node.h>
#include <set>

namespace scrawble
{
    class arc
    {
       public:
        typedef char value_type;
        typedef std::set<value_type> value_list;

        arc(const node &destination);

        arc(const arc &other) = default;
        arc(arc &&other) = default;
        virtual ~arc() = default;
        arc &operator=(const arc &other) = default;
        arc &operator=(arc &&other) = default;

        bool operator==(const arc &other) const;

        arc &push_final_value(const value_type &value);

        std::set<path> final_paths() const;

        const node &destination() const;

       private:
        node destination_;
        value_list values_;
    };
}

#endif
