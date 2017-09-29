#ifndef SCRAWBLE_GADDAG_H
#define SCRAWBLE_GADDAG_H

#include <string>
#include "node.h"

namespace scrawble
{
    class Gaddag
    {
       public:
        Gaddag();

        Gaddag &add(const std::string &value);

        std::set<std::string> find(const std::string &hook, const std::string &rack) const;

       private:
        Node::Ptr root_;
    };
}

#endif
