#ifndef SCRAWBLE_GADDAG_H
#define SCRAWBLE_GADDAG_H

#include <scrawble/node.h>
#include <set>
#include <string>

namespace scrawble
{
    class gaddag
    {
       public:
        gaddag &push(const std::string &word);

        std::set<std::string> find(const std::string &substr) const;

       private:
        typedef char value_type;
        typedef std::vector<value_type> value_list;

        node root_;
    };
}

#endif
