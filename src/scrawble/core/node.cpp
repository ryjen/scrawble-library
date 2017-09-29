#include <scrawble/core/node.h>
#include <algorithm>
#include <cassert>
#include <string>

namespace scrawble
{
    Node::Type Node::assert_letter(const Type &value)
    {
        assert(isalpha(value) || value == Node::Eow);
        return tolower(value);
    }

    Node::Node() : value_(Root)
    {
    }
    Node::Node(const Type &value) : value_(assert_letter(value))
    {
    }

    Node::Node::Node(const Node &other) : value_(other.value_), children_(other.children_)
    {
    }

    Node::Node(Node &&other) : value_(std::move(other.value_)), children_(std::move(other.children_))
    {
    }

    Node::~Node()
    {
    }

    Node::Ptr Node::operator[](const Type &index) const
    {
        auto it = children_.find(index);
        return it->second;
    }

    Node::Ptr Node::child(const Type &index) const
    {
        auto it = children_.find(index);
        return it->second;
    }

    Node &Node::operator=(const Node &other)
    {
        value_ = other.value_;
        children_ = other.children_;
        return *this;
    }
    Node &Node::operator=(Node &&other)
    {
        value_ = std::move(other.value_);
        children_ = std::move(other.children_);
        return *this;
    }

    Node::Type Node::letter() const
    {
        return value_;
    }

    Node &Node::set_letter(const Type &value)
    {
        value_ = assert_letter(value);
        return *this;
    }

    Node::Ptr Node::add_child(const Type &value, const Ptr &node)
    {
        auto val = assert_letter(value);
        auto it = children_.find(val);

        if (it == children_.end()) {
            children_[val] = node == nullptr ? std::make_shared<Node>(val) : node;
        }

        return children_[val];
    }

    bool Node::operator==(const Node &other) const
    {
        return value_ == other.value_;
    }

    bool Node::operator==(const Type &other) const
    {
        return value_ == other;
    }

    bool Node::contains(const Type &other) const
    {
        return children_.count(other) > 0;
    }

    void Node::visit(const Visitor &visitor) const
    {
        for (const auto &entry : children_) {
            visitor(entry.first, entry.second);
        }
    }
}