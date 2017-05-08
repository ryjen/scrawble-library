#ifndef SCRAWBLE_LEXICON_NODE_H
#define SCRAWBLE_LEXICON_NODE_H

#include <memory>
#include <set>
#include <string>

class node
{
   public:
    typedef std::shared_ptr<node> ptr;
    typedef std::set<ptr> list_type;

    typedef list_type::iterator iterator;
    typedef list_type::const_iterator const_iterator;

    iterator begin()
    {
        return children_.begin();
    }
    iterator end()
    {
        return children_.end();
    }
    node() : value_()
    {
    }
    node(char value) : value_(value)
    {
    }

    virtual ~node()
    {
    }
    char value() const
    {
        return value_;
    }
    void value(char value)
    {
        value_ = value;
    }
    bool marker() const
    {
        return marker_;
    }
    void mark(bool value)
    {
        marker_ = value;
    }

    node::ptr find(char c)
    {
        for (auto node : children_) {
            if (node->value_ == c) {
                return node;
            }
        }
        return nullptr;
    }

    node &push(const ptr &value)
    {
        children_.insert(value);
        return *this;
    }

    node::ptr push(char c)
    {
        auto n = std::make_shared<node>(c);
        children_.insert(n);
        return n;
    }

    const list_type children() const
    {
        return children_;
    }

   private:
    char value_;
    bool marker_;
    list_type children_;
};


#endif
