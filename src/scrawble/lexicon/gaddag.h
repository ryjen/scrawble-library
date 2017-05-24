#ifndef SCRAWBLE_LEXICON_GADDAG_H
#define SCRAWBLE_LEXICON_GADDAG_H

#include <scrawble/lexicon/trie.h>
#include <string>

namespace scrawble
{
    namespace lexicon
    {
        class gaddag : public trie
        {
           private:
            node::ptr reverse_;

           public:
            gaddag();
            void push(const std::string &word);
            node::ptr reverse() const;

           private:
            void push_prefix(const std::string &prefix);
        };
    }
}
#endif
