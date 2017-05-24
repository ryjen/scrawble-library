#ifndef _FILE_READER_H
#define _FILE_READER_H

#include <fstream>
#include <json.hpp>
#include <string>

class file_reader
{
   public:
    class line : public std::string
    {
       public:
        friend std::istream &operator>>(std::istream &is, line &line);
    };

    typedef std::istream_iterator<line> iterator;

    file_reader(const std::string &filePath) : input_(filePath)
    {
        assert(input_.is_open());
    }
    virtual ~file_reader()
    {
        input_.close();
    }

    nlohmann::json to_json()
    {
        nlohmann::json j;
        // save current state
        auto state = input_.rdstate();
        auto pos = input_.tellg();

        // reset
        input_.clear();
        input_.seekg(0);

        // convert
        input_ >> j;

        // restore current state
        input_.clear(state);
        input_.seekg(pos);

        return j;
    }

    iterator begin()
    {
        return iterator(input_);
    }
    iterator end()
    {
        return iterator();
    }

   private:
    std::ifstream input_;
};

inline std::istream &operator>>(std::istream &is, file_reader::line &line)
{
    return std::getline(is, line);
}

#endif