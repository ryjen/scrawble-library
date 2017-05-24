#ifndef SCRAWBLE_LEXICON_TRIE_H
#define SCRAWBLE_LEXICON_TRIE_H

#include <scrawble/lexicon/node.h>
#include <iostream>

namespace scrawble
{
    namespace lexicon
    {
        class trie
        {
           public:
            typedef node::iterator iterator;
            typedef node::const_iterator const_iterator;

            trie() : root_()
            {
                root_ = std::make_shared<node>(lexicon::node::BEGIN);
                end_ = std::make_shared<node>(lexicon::node::EMPTY);
                nodeCount_ = 1;
                wordCount_ = 0;
                maxDepth_ = 0;
            }
            virtual ~trie()
            {
            }

            iterator begin()
            {
                return root_->begin();
            }

            iterator begin() const
            {
                return root_->begin();
            }

            iterator end()
            {
                return root_->end();
            }

            iterator end() const
            {
                return root_->end();
            }

            virtual void push(const std::string &word)
            {
                if (word.empty()) {
                    return;
                }

                auto current = root_;

                for (auto it = word.begin(); it != word.end(); ++it) {
                    auto child = current->find(*it);
                    if (child != nullptr) {
                        current = child;
                    } else {
                        current = current->push(*it);
                        nodeCount_++;
                    }
                }

                current->mark(true);

                if (word.length() > maxDepth_) {
                    maxDepth_ = word.length();
                }
                wordCount_++;
            }

            bool contains(const std::string &word)
            {
                auto current = root_;

                for (auto ch : word) {
                    auto tmp = current->find(ch);
                    if (tmp == nullptr) {
                        return false;
                    }
                    current = tmp;
                }
                return current->marker();
            }

            void erase(const std::string &word)
            {
            }

            void print(std::ostream &out, const node::ptr &node, int offset) const
            {
                for (int i = 0; i < offset; i++) {
                    out << " ";
                }
                out << "↳ " << node->value() << std::endl;

                for (auto &child : *node) {
                    print(out, child, offset + 1);
                }
            }

            void print(std::ostream &out) const
            {
                print(out, root_, 0);
            }

           protected:
            node::ptr root_;
            node::ptr end_;
            unsigned wordCount_;
            unsigned long nodeCount_;
            short maxDepth_;
        };
    }
}

#endif
