#ifndef SCRAWBLE_NODE_H
#define SCRAWBLE_NODE_H

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>

namespace scrawble
{
    class Node : public std::enable_shared_from_this<Node>
    {
       public:
        typedef std::shared_ptr<Node> Ptr;
        typedef char Type;

       private:
        bool root_;
        Type letter_;
        bool terminal_;
        Node::Ptr parentNode_;
        std::map<Type, Ptr> childNodes_;

        /**
         * A special character that represents a crossing of the anchor during processing; if that makes much sense.
         */
       public:
        static const char CROSS_ANCHOR_CHAR;

        /**
         * Creates and returns a root node.
         *
         * @return  A node that return <code>true</code> when {@link #isRoot()} is invoked.
         */
        static Node::Ptr createRootNode()
        {
            return std::make_shared<Node>();
        }

        /**
         * Private constructor creates a node with root as <code>true</code>,
         * terminal as <code>false</code>, letter as 0, and parentNode as <code>null</code>.  In other words,
         * a root node.
         */
        Node() : root_(true), letter_(0), terminal_(false)
        {
        }

        /**
         * The constructor to be used to create a non-root node.
         *
         * @param letter        The letter for this node to represent.
         * @param parentNode    The required parent node.
         *
         * @throws IllegalLetterException   When the word contains a character that is not a letter a-z, A-Z, or
         *                                  {@value #CROSS_ANCHOR_CHAR}
         */
        Node(Type letter, bool terminal, const Ptr& parentNode)
        {
            assert(isalpha(letter) || letter == CROSS_ANCHOR_CHAR);

            letter_ = tolower(letter);
            parentNode_ = parentNode;
            terminal_ = terminal;
        }

       protected:
        void setRoot(bool root)
        {
            root_ = root;
        }

        void setParentNode(const Ptr& node)
        {
            parentNode_ = node;
        }

       public:
        bool isRoot() const
        {
            return root_;
        }

        /**
         * Determines whether this node's letter is the {@link #CROSS_ANCHOR_CHARACTER}.
         *
         * @return  <code>true</code> if this node's letter is {@value #CROSS_ANCHOR_CHARACTER}
         *
         * @see TrieNode#isCrossAnchorNode()
         */
        bool isCrossAnchorNode() const
        {
            return (letter_ == CROSS_ANCHOR_CHAR);
        }

        Type getLetter() const
        {
            return letter_;
        }

        void setLetter(Type letter)
        {
            letter_ = letter;
        }

        void setTerminal(bool terminal)
        {
            terminal_ = terminal;
        }

        bool isTerminal() const
        {
            return terminal_;
        }

        Node::Ptr getParentNode() const
        {
            return parentNode_;
        }

        Node::Ptr addChildNode(Type letter, bool terminal)
        {
            Type lowerLetter = tolower(letter);

            // see if this child node already exists
            auto existingChildNode = getChildNode(lowerLetter);
            assert(existingChildNode == nullptr);

            auto childNode = std::make_shared<Node>(lowerLetter, terminal, shared_from_this());

            childNodes_[lowerLetter] = childNode;

            return childNode;
        }

        Node::Ptr getOrAddChildNode(Type letter, bool terminal)
        {
            Type lowerLetter = tolower(letter);

            // see if this child node already exists
            auto node = getChildNode(lowerLetter);
            if (node == nullptr) {
                node = std::make_shared<Node>(lowerLetter, terminal, shared_from_this());
                childNodes_[lowerLetter] = node;
            } else {
                if (terminal_) {
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
        Node::Ptr addChildCrossAnchorNode()
        {
            return addChildNode(CROSS_ANCHOR_CHAR, false);
        }

        Node::Ptr getChildNode(Type letter) const
        {
            auto it = childNodes_.find(letter);

            if (it == childNodes_.end()) {
                return nullptr;
            }
            return it->second;
        }

        Node::Ptr getCrossAnchorNode() const
        {
            auto it = childNodes_.find(CROSS_ANCHOR_CHAR);

            if (it == childNodes_.end()) {
                return nullptr;
            }
            return it->second;
        }

        std::vector<Node::Ptr> getChildNodes() const
        {
            std::vector<Node::Ptr> values(childNodes_.size());

            for (auto& entry : childNodes_) {
                values.push_back(entry.second);
            }
            return values;
        }

        std::string toString() const
        {
            std::string sb("root=");
            sb += root_;

            sb += (", letter='");
            if (letter_ != 0) {
                sb += (letter_);
            }

            sb += ("', terminal=");
            sb += std::to_string(terminal_);

            sb += (", parent=[");
            if (parentNode_ != nullptr) {
                if (parentNode_->isRoot()) {
                    sb += ("root");
                } else {
                    sb += ("'");
                    sb += (parentNode_->getLetter());
                    sb += ("'");
                }
            }

            sb += ("], children={");
            int i = 0;
            int length = childNodes_.size();

            auto sortedChildNodes = getChildNodes();
            std::sort(sortedChildNodes.begin(), sortedChildNodes.end(), [](const Node::Ptr& n1, const Node::Ptr& n2) {
                int result = n1->getLetter() - n2->getLetter();
                return result;
            });

            for (auto& childNode : sortedChildNodes) {
                sb += ("'");
                sb += (childNode->getLetter());
                sb += ("'");
                if ((i + 1) != length) {
                    sb += (",");
                }
                i++;
            }
            sb += ("}");

            return sb;
        }
    };
}

#endif
