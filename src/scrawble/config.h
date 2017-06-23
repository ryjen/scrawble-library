#ifndef SCRAWBLE_CONFIG_H
#define SCRAWBLE_CONFIG_H

#include <string>
#include <vector>

namespace scrawble
{
    class Config
    {
       public:
        Config();

        typedef struct Tile {
            int score;
            int count;
            char letter;
            Tile(int score, int count, char letter) : score(score), count(count), letter(letter)
            {
            }
        } Tile;

        const std::vector<Tile> &tile_distributions() const;

        const std::string &dictionary_file_name() const;

        virtual void load(const std::string &filename) = 0;

       protected:
        std::vector<Tile> letters_;
        std::string dictionary_;
    };
}

#endif
