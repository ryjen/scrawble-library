#include <scrawble/lexicon/node.h>

namespace scrawble
{
    namespace lexicon
    {
        const char node::BEGIN = '~';
        const char node::EMPTY = '_';
        const char node::DIRSYM = '<';

        node::iterator node::begin()
        {
            return children_.begin();
        }
        node::iterator node::begin() const
        {
            return children_.begin();
        }
        node::iterator node::end()
        {
            return children_.end();
        }
        node::iterator node::end() const
        {
            return children_.end();
        }

        node::node() : value_()
        {
        }
        node::node(char value) : value_(value)
        {
        }

        node::~node()
        {
        }
        char node::value() const
        {
            return value_;
        }
        void node::value(char value)
        {
            value_ = value;
        }
        bool node::marker() const
        {
            return marker_;
        }
        void node::mark(bool value)
        {
            marker_ = value;
        }

        node::ptr node::find(char c) const
        {
            char ch = toupper(c);

            for (auto node : children_) {
                if (node->value_ == ch) {
                    return node;
                }
            }
            return nullptr;
        }

        node &node::push(const ptr &value)
        {
            children_.insert(value);
            return *this;
        }

        node::ptr node::push(char c)
        {
            auto n = std::make_shared<node>(toupper(c));
            children_.insert(n);
            return n;
        }

        const node::list_type node::children() const
        {
            return children_;
        }
    }
}
