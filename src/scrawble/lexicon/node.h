#ifndef SCRAWBLE_LEXICON_NODE_H
#define SCRAWBLE_LEXICON_NODE_H

#include <memory>
#include <set>
#include <string>

namespace lexicon
{
    class node
    {
       public:
        static const char BEGIN;
        static const char EMPTY;
        static const char DIRSYM;

        typedef std::shared_ptr<node> ptr;
        typedef std::set<ptr> list_type;

        typedef list_type::iterator iterator;
        typedef list_type::const_iterator const_iterator;

        iterator begin();
        iterator begin() const;
        iterator end();
        iterator end() const;

        node();
        node(char value);

        virtual ~node();
        char value() const;
        void value(char value);
        bool marker() const;
        void mark(bool value);

        node::ptr find(char c) const;

        node &push(const ptr &value);

        node::ptr push(char c);

        const list_type children() const;

       private:
        char value_;
        bool marker_;
        list_type children_;
    };
}

#endif
