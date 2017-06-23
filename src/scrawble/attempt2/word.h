#ifndef SCRAWBLE_WORD_H
#define SCRAWBLE_WORD_H

#include <iterator>
#include <string>
#include <vector>

namespace scrawble
{
    class path;

    class word
    {
       public:
        typedef char value_type;
        typedef std::vector<value_type> value_list;
        typedef std::shared_ptr<word> ptr;

        word(const value_list &values);
        word(const std::string &value);
        
        word(const word &other);
        word(word &&other);
        virtual ~word();
        word &operator=(const word &other);
        word &operator=(word &&other);

        std::string to_string() const;

        std::vector<path> delimited_paths() const;

        bool operator==(const word &other) const;

       private:
        value_list values_;
    };
}

#endif
