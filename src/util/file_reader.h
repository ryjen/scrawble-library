#ifndef _FILE_READER_H
#define _FILE_READER_H

#include <fstream>
#include <json.hpp>
#include <string>

class FileReader {
   public:
    class Line : public std::string {
       public:
        friend std::istream &operator>>(std::istream &is, Line &line);
    };

    typedef std::istream_iterator<Line> iterator;

    FileReader(const std::string &filePath) : input_(filePath) {
        assert(input_.is_open());
    }

    FileReader(const FileReader &other) = delete;
    FileReader(FileReader &&other) = delete;
    FileReader &operator=(const FileReader &other) = delete;
    FileReader &operator=(FileReader &&other) = delete;

    virtual ~FileReader() {
        input_.close();
    }

    nlohmann::json to_json() {
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

    iterator begin() {
        return iterator(input_);
    }
    iterator end() {
        return iterator();
    }

   private:
    std::ifstream input_;
};

inline std::istream &operator>>(std::istream &is, FileReader::Line &line) {
    return std::getline(is, line);
}

#endif