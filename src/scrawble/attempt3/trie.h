#ifndef SCRAWBLE_TRIE_H
#define SCRAWBLE_TRIE_H

#include <scrawble/core/node.h>
#include <util/util.h>

namespace scrawble
{
    class Trie
    {
       public:
        typedef std::shared_ptr<Trie> Ptr;

       private:
        Node::Ptr root_;

        // not required by the Interface
        int nodeCount_;
        int wordCount_;

       public:
        Trie() : root_(Node::createRootNode())
        {
        }

        void setRoot(const Node::Ptr& node)
        {
            root_ = node;
        }

        Node::Ptr getRoot() const
        {
            return root_;
        }

        void addWord(const std::string& letters)
        {
            assert(!letters.empty());

            assert(isalpha(letters));

            if (addNodes(letters)) {
                // if any new nodes were added, then this signifies that this word did not already exist
                wordCount_++;
            }

            // add variations of this word that contain the cross anchor character
            /*
             * Example for the word "language":
                    ANGUAGE#L
                    NGUAGE#AL
                    GUAGE#NAL
                    UAGE#GNAL
                    AGE#UGNAL
                    GE#AUGNAL
                    E#GAUGNAL
            */
            if (letters.length() <= 1) {
                return;
            }

            // create a working array and add the "cross anchor character" to the end
            std::string variations;
            std::copy(letters.begin() + 1, letters.end(), std::back_inserter(variations));
            variations += Node::CROSS_ANCHOR_CHAR;
            variations += letters[0];

            char first = 0;
            int crossAnchorCharIndex = letters.length() - 1;
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
        }
        /**
         * Adds nodes to the tree that don't already exist for the characters in the character array.
         * <p>
         * Assumes that the char[] is not <code>null<code>.
         *
         * @param letters       The character array to add.
         *
         * @return  Whether or not this action resulted in the addition of a new terminal node.
         */
        bool addNodes(const std::string& letters)
        {
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

        int getNodeCount()
        {
            return nodeCount_;
        }

        int getWordCount()
        {
            return wordCount_;
        }
    };
}  // namespace scrawble
#endif
