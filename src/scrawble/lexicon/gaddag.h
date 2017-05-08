#ifndef SCRAWBLE_LEXICON_GADDAG_H
#define SCRAWBLE_LEXICON_GADDAG_H

#include <string>
#include "trie.h"

class gaddag : public trie
{
   private:
    node::ptr reverse_;

   public:
    gaddag() : trie()
    {
        reverse_ = std::make_shared<node>('<');
        nodeCount_++;
    }
    void push(const std::string &word)
    {
        if (word.empty()) {
            return;
        }

        trie::push(word);

        std::string prefix;
        for (int i = 1, size = word.length(); i < size; ++i) {
            prefix = word.substr(0, i);
            std::string reverse(prefix.rbegin(), prefix.rend());
            push_prefix(prefix + ">" + word.substr(i));
        }
        std::string reverse(word.rbegin(), word.rend());
        push_prefix(reverse + ">");
    }

   private:
    void push_prefix(const std::string &prefix)
    {
        if (prefix.empty()) {
            return;
        }
        node::ptr tmp = reverse_;

        for (auto ch : prefix) {
            auto child = tmp->find(ch);
            if (child != nullptr) {
                tmp = child;
            } else {
                tmp = tmp->push(ch);
                nodeCount_++;
            }
        }

        tmp->mark(true);
    }
};

#endif
