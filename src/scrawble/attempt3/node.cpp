#include <scrawble/attempt3/node.h>
#include <cassert>
#include <vector>

namespace scrawble
{
    Node::Node() : root_(true), childNodes_()
    {
    }

    Node::Node(const Type &letter, bool terminal, const Node::Ptr &parentNode)
        : letter_(tolower(letter)), terminal_(terminal), parentNode_(parentNode)
    {
        assert(isalpha(letter) || letter == CROSS_ANCHOR_CHAR);
    }

    Node &Node::setRoot(bool value)
    {
        root_ = value;
        return *this;
    }

    bool Node::isRoot() const
    {
        return root_;
    }

    bool Node::isCrossAnchorNode() const
    {
        return letter_ == CROSS_ANCHOR_CHAR;
    }

    Node &Node::setLetter(const Type &value)
    {
        letter_ = value;
        return *this;
    }

    Node::Type Node::getLetter() const
    {
        return letter_;
    }

    Node &Node::setTerminal(bool terminal)
    {
        terminal_ = terminal;
        return *this;
    }

    bool Node::isTerminal() const
    {
        return terminal_;
    }

    Node &Node::setParentNode(const Node::Ptr &node)
    {
        parentNode_ = node;
        return *this;
    }

    Node::Ptr Node::getParentNode() const
    {
        return parentNode_;
    }

    Node::Ptr Node::addChildNode(const Type &letter, bool terminal)
    {
        char lowerLetter = tolower(letter);

        // see if this child node already exists
        Node::Ptr existingChildNode = getChildNode(lowerLetter);
        assert(existingChildNode == nullptr);

        Node::Ptr childNode = std::make_shared<Node>(lowerLetter, terminal, shared_from_this());

        childNodes_[lowerLetter] = childNode;

        return childNode;
    }

    Node::Ptr Node::getOrAddChildNode(const Type &letter, bool terminal)
    {
        Node::Ptr node = nullptr;

        Type lowerLetter = tolower(letter);

        // see if this child node already exists
        node = getChildNode(lowerLetter);
        if (node == nullptr) {
            node = std::make_shared<Node>(lowerLetter, terminal, shared_from_this());
            childNodes_[lowerLetter] = node;
        } else {
            if (terminal) {
                // update this node to be terminal
                node->setTerminal(true);
            }
        }

        return node;
    }

    /**
     * Adds a child node with a letter equal to {@value #CROSS_ANCHOR_CHARACTER}.
     * <p>
     * A cross anchor node cannot be a terminal node.
     *
     * @see #addChildNode(char, boolean)
     */
    Node::Ptr Node::addChildCrossAnchorNode()
    {
        return addChildNode(CROSS_ANCHOR_CHAR, false);
    }

    Node::Ptr Node::getChildNode(const Type &letter) const
    {
        auto it = childNodes_.find(tolower(letter));

        if (it == childNodes_.end()) {
            return nullptr;
        }
        return it->second;
    }

    Node::Ptr Node::getCrossAnchorNode() const
    {
        auto it = childNodes_.find(CROSS_ANCHOR_CHAR);

        if (it == childNodes_.end()) {
            return nullptr;
        }
        return it->second;
    }

    std::vector<Node::Ptr> Node::getChildNodes() const
    {
        std::vector<Node::Ptr> values(childNodes_.size());

        for (auto &entry : childNodes_) {
            values.push_back(entry.second);
        }
        return values;
    }

}  // namespace scrawble