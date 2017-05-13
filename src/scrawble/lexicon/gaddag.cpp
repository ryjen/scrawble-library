#include <scrawble/lexicon/gaddag.h>

namespace lexicon
{
    gaddag::gaddag() : trie()
    {
        reverse_ = std::make_shared<node>('<');
        nodeCount_++;
    }

    node::ptr gaddag::reverse() const
    {
        return reverse_;
    }

    void gaddag::push(const std::string &word)
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

    void gaddag::push_prefix(const std::string &prefix)
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
}
