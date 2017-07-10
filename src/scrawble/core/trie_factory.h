#ifndef SCRAWBLE_TRIE_FACTORY_H
#define SCRAWBLE_TRIE_FACTORY_H

#include <util/file_reader.h>

namespace scrawble
{
    class TrieFactory
    {
       private:
        FileReader dictionary_;

       public:
        virtual Trie::Ptr createTrie() = 0;

        /**
         * Creates a {@link Trie} object by reading each word found in the {@link DictionaryReader}.
         *
         * @param dictionary	The {@link DictionaryReader} to create the {@link Trie} from
         *
         * @return	A {@link Trie} using the words from the {@link DictionaryReader}
         */
       protected:
        Trie::Ptr createTrie(const FileReader& dictionary)
        {
            Trie t;

            int wordCount = 0;
            for (auto& word : dictionary) {
                t->addWord(word);
                wordCount++;
            }
            return t;
        }

        FileReader getDictionary()
        {
            return dictionary_;
        }

        void setDictionary(const FileReader& dictionary)
        {
            dictionary_ = dictionary;
        }
    };
}

#endif
