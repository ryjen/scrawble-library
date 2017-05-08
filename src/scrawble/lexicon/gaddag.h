#ifndef SCRAWBLE_LEXICON_GADDAG_H
#define SCRAWBLE_LEXICON_GADDAG_H

#include <string>
#include "trie.h"

class gaddag : public trie
{
   private:
    node::ptr reverse_;

   public:
    gaddag();
    void push(const std::string &word);

   private:
    void push_prefix(const std::string &prefix);
};

#endif
