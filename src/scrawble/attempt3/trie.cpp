#include <scrawble/attempt3/trie.h>
#include <util/util.h>
#include <cassert>

namespace scrawble {

    Trie::Trie() : root_() {
    }

    Trie &Trie::setRoot(const Node::Ptr &value) {
        root_ = value;
        return *this;
    }

    Node::Ptr Trie::getRoot() const {
        return root_;
    }

    Trie &Trie::addWord(const std::string &word) {
        assert(!word.empty());

        assert(is_alpha(word));

        if (addNodes(word)) {
            wordCount_++;
        }

        if (word.length() == 1) {
            return *this;
        }

        std::string variations;

        std::copy(word.begin() + 1, word.end() - 1, variations.begin());
        variations += Node::CROSS_ANCHOR_CHAR;
        variations += word[0];

        char first = 0;
        int crossAnchorCharIndex = word.length() - 1;
        int i = 0;
        while (true) {
            addNodes(variations);

            if (crossAnchorCharIndex <= 1) {
                break;
            }

            // rotate
            first = variations[0];
            // replace the cross anchor character
            variations[crossAnchorCharIndex] = first;
            crossAnchorCharIndex--;

            for (i = 0; i < crossAnchorCharIndex; i++) {
                // move characters backwards
                variations[i] = variations[i + 1];
            }
            variations[crossAnchorCharIndex] = Node::CROSS_ANCHOR_CHAR;
        }
        return *this;
    }

    bool Trie::addNodes(const std::string &letters) {
        assert(!letters.empty());

        Node::Ptr node = root_;

        bool terminal = false;
        Node::Ptr childNode = nullptr;
        for (int offset = 0; offset < letters.length(); offset++) {
            terminal = (offset + 1 == letters.length());
            childNode = node->getChildNode(letters[offset]);

            if (childNode == nullptr) {
                node = node->addChildNode(letters[offset], terminal);
                nodeCount_++;
            } else {
                // only update if not already terminal
                terminal = terminal && !childNode->isTerminal();
                if (terminal) {
                    childNode->setTerminal(true);
                }
                node = childNode;
            }
        }  // ~for

        return terminal;
    }

    int Trie::getNodeCount() const {
        return nodeCount_;
    }
    int Trie::getWordCount() const {
        return wordCount_;
    }
}  // namespace scrawble