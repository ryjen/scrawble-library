#ifndef SCRAWBLE_TRIE_FACTORY_H
#define SCRAWBLE_TRIE_FACTORY_H

#include <util/file_reader.h>

namespace scrawble {
    class TrieFactory {
       public:
        virtual Trie::Ptr createTrie() const = 0;
    };

    class FileBasedTrieFactory : public TrieFactory {
       private:
        std::string fileName_;

       public:
        FileBasedTrieFactory(const std::string& fileName) : fileName_(fileName) {
        }

        Trie::Ptr createTrie() const {
            FileReader dictionary(fileName_);
            auto t = std::make_shared<Trie>();

            int wordCount = 0;
            for (auto& word : dictionary) {
                t->addWord(word);
                wordCount++;
            }
            return t;
        }
    };
}  // namespace scrawble

#endif
