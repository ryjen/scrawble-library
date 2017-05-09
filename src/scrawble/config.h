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

    config();

    config(const std::string &filePath);

    typedef struct tile {
        int score;
        int count;
        std::string letter;
        tile(int score, int count, const std::string &letter) : score(score), count(count), letter(letter)
        {
        }
    } tile;

    const std::vector<tile> &letters() const;

    const std::string &dictionary() const;

    void load(const std::string &filepath);

    void load();

   private:
    std::vector<tile> letters_;
    std::string dictionary_;
};

class file_reader
{
   public:
    class line : public std::string
    {
       public:
        friend std::istream &operator>>(std::istream &is, line &line);
    };

    typedef std::istream_iterator<line> iterator;

    file_reader(const std::string &filePath);
    virtual ~file_reader();

    nlohmann::json to_json();

    iterator begin();
    iterator end();

   private:
    std::ifstream input_;
};

#endif
