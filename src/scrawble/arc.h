#ifndef SCRAWBLE_ARC_H
#define SCRAWBLE_ARC_H

#include <set>

namespace scrawble
{
    class node;
    class path;
    
    class arc
    {
       public:
        typedef char value_type;
        typedef std::set<value_type> value_list;
        typedef std::shared_ptr<arc> ptr;
        typedef std::shared_ptr<node> node_ptr;
        typedef std::shared_ptr<path> path_ptr;

        arc(const node_ptr &destination);

        arc(const arc &other);
        arc(arc &&other);
        virtual ~arc();
        arc &operator=(const arc &other);
        arc &operator=(arc &&other);

        bool operator==(const arc &other) const;

        arc &push_final_value(const value_type &value);

        std::set<path_ptr> final_paths() const;

        const node_ptr &destination() const;

       private:
        node_ptr destination_;
        value_list values_;
    };
}

#endif
