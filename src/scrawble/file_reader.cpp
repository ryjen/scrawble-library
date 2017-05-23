#include <scrawble/file_reader.h>
#include <unistd.h>

namespace scrawble
{
    class file_iterator : public std::iterator<std::forward_iterator_tag, std::string>
    {
       public:
        file_iterator(file_reader* reader) : reader_(reader)
        {
            if (reader_) {
                reader_->getline(line_);
            }
        }
        file_iterator() : reader_(NULL)
        {
        }

        reference operator*()
        {
            return line_;
        }

        iterator& operator++()
        {
            if (reader_) {
                reader_->getline(line_);
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }

        bool operator==(const file_iterator& other) const
        {
            return reader_ == other.reader_ && line_ == other.line_;
        }
        bool operator!=(const file_iterator& other) const
        {
            return !operator==(other);
        }

       private:
        file_reader* reader_;
        std::string line_;
    };

    file_reader::file_reader(int file_desc) : desc_(file_desc)
    {
    }

    file_reader::~file_reader()
    {
        if (desc_ > 0) {
            close(desc_);
            desc_ = -1;
        }
    }

    bool file_reader::is_open() const
    {
        return desc_ > 0;
    }

    void file_reader::getline(std::string& line)
    {
        char ch;

        do {
            int bytes = read(desc_, &ch, 1);

            switch (bytes) {
                case 1:
                    if (ch == '\n') {
                        return;
                    }
                    line += ch;
                    break;
                case 0:
                    return;
                case -1:
                    perror("error reading line");
                    return;
            }
        } while (is_open());
    }

    file_reader::iterator file_reader::begin()
    {
        return file_iterator(this);
    }

    file_reader::iterator file_reader::end()
    {
        return file_iterator();
    }
}