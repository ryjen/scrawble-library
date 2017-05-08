#ifndef SCRAWBLE_CONFIG_H
#define SCRAWBLE_CONFIG_H

#include <fstream>
#include <json.hpp>
#include <string>
#include <vector>

class config
{
   public:
    static constexpr const char *DEFAULT_CONFIG_FILE = "assets/english.json";

    config()
    {
        load(DEFAULT_CONFIG_FILE);
    }

    config(const std::string &filePath)
    {
        load(filePath);
    }

    typedef struct tile {
        int score;
        int count;
        std::string letter;
        tile(int score, int count, const std::string &letter) : score(score), count(count), letter(letter)
        {
        }
    } tile;

    const std::vector<tile> &letters() const
    {
        return letters_;
    }

    const std::string &dictionary() const
    {
        return dictionary_;
    }

    void load(const std::string &filepath);

   private:
    std::vector<tile> letters_;
    std::string dictionary_;
};

class file_reader
{
   public:
    typedef std::istream_iterator<std::string> iterator;
    typedef const std::istream_iterator<std::string> const_iterator;

    file_reader(const std::string &filePath);
    virtual ~file_reader();

    nlohmann::json to_json();

    iterator begin();
    iterator end();

   private:
    std::ifstream input_;
};

#endif
