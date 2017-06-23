#ifndef SCRAWBLE_NODE_H
#define SCRAWBLE_NODE_H

#include <map>
#include <vector>

namespace scrawble
{
    class arc;
    class path;
    
    class node : std::enable_shared_from_this<node>
    {
       public:
        typedef char value_type;
        typedef std::shared_ptr<node> ptr;
        typedef std::shared_ptr<const node> const_ptr;
        typedef ptr destination_type;
        typedef std::vector<value_type> value_list;
        typedef std::vector<destination_type> destination_list;
        typedef std::shared_ptr<arc> arc_ptr;
        typedef std::shared_ptr<path> path_ptr;
        
        node();
        node(const node &other);
        node(node &&other);
        virtual ~node();
        node &operator=(const node &other);
        node &operator=(node &&other);

        bool operator==(const node &other) const;

        arc_ptr create_arc(const value_type &value, const destination_type &destination = destination_type());

        arc_ptr create_final_arc(const value_type &value, const value_type &final,
                             const destination_type &destination = destination_type());

        destination_type create_path(const value_list &values,
                                     const destination_list &destinations = destination_list());

        destination_type create_final_path(const value_list &values,
                                           const destination_list &destinations = destination_list());

        bool is_arc(const value_type &value) const;

        bool is_path(const value_list &values) const;

        bool is_final_path(const value_list &values) const;

        const const_ptr &follow_arc(const value_type &value) const;

        const const_ptr &follow_path(const value_list &values) const;

        std::vector<path_ptr> final_paths() const;

       private:
        static std::tuple<value_list, value_type, value_type> chop_last_pair(const value_list &values);

        std::map<value_type, arc_ptr> arcs_;
    };
}

#endif
