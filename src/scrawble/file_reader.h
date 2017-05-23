#ifndef SCRAWBLE_FILE_READER_H
#define SCRAWBLE_FILE_READER_H

#include <fstream>
#include <string>

namespace scrawble
{
    class file_reader
    {
       public:
        typedef std::iterator<std::forward_iterator_tag, std::string> iterator;

        file_reader(int file_desc);

        virtual ~file_reader();

        iterator begin();
        iterator end();

        bool is_open() const;

        void getline(std::string& line);

       private:
        int desc_;
    };
}

#endif
