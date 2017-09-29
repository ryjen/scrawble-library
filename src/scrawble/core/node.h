#ifndef SCRAWBLE_NODE_H
#define SCRAWBLE_NODE_H

#include <map>
#include <memory>
#include <set>

namespace scrawble
{
    class Node
    {
       public:
        typedef char Type;
        typedef std::shared_ptr<Node> Ptr;
        typedef std::function<void(const Type &, const Ptr &)> Visitor;
        constexpr static const char Break = '+';
        constexpr static const char Eow = '$';
        constexpr static const char Root = '^';

        Node();
        Node(const Type &value);
        Node(const Node &other);
        Node(Node &&other);
        ~Node();

        Node &operator=(const Node &other);
        Node &operator=(Node &&other);

        Type letter() const;
        Node &set_letter(const Type &value);

        Node::Ptr add_child(const Type &letter, const Ptr &node = nullptr);

        bool contains(const Type &other) const;

        void visit(const Visitor &visitor) const;

        Node::Ptr operator[](const Type &index) const;
        Node::Ptr child(const Type &index) const;

        bool operator==(const Node &other) const;
        bool operator==(const Type &other) const;

       private:
        static Type assert_letter(const Type &value);
        std::map<Type, Ptr> children_;
        Type value_;
    };
}

#endif
