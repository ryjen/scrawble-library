#ifndef SCRAWBLE_NODE_H
#define SCRAWBLE_NODE_H

#include <map>
#include <vector>

namespace scrawble
{
    class path;
    class arc;

    class node
    {
       public:
        typedef char value_type;
        typedef node destination_type;
        typedef std::vector<value_type> value_list;
        typedef std::vector<node> destination_list;

        bool operator==(const node &other) const;

        arc create_arc(const value_type &value, const destination_type &destination = node());

        arc create_final_arc(const value_type &value, const value_type &final,
                             const destination_type &destination = destination_type());

        destination_type create_path(const value_list &values,
                                     const destination_list &destinations = destination_list());

        destination_type create_final_path(const value_list &values,
                                           const destination_list &destinations = destination_list());

        bool is_arc(const value_type &value) const;

        bool is_path(const value_list &values) const;

        bool is_final_path(const value_list &values) const;

        const node &follow_arc(const value_type &value) const;

        const node &follow_path(const value_list &values) const;

        std::vector<path> final_paths() const;

       private:
        static std::tuple<value_list, value_type, value_type> chop_last_pair(const value_list &values);

        std::map<value_type, arc> arcs_;
    };
}

#endif
