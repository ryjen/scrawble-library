#ifndef SCRAWBLE_TRIE_H
#define SCRAWBLE_TRIE_H

#include <scrawble/attempt3/node.h>
#include <memory>

namespace scrawble {
    class Trie {
       public:
        typedef std::shared_ptr<Node> type;

        Trie();

        Trie &setRoot(const Node::Ptr &value);
        Node::Ptr getRoot() const;

        Trie &addWord(const std::string &word);

        bool addNodes(const std::string &values);

        int getNodeCount() const;
        int getWordCount() const;

       private:
        type root_;
        int nodeCount_;
        int wordCount_;
    };
}  // namespace scrawble

#endif
