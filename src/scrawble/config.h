#ifndef SCRAWBLE_CONFIG_H
#define SCRAWBLE_CONFIG_H

#include <string>
#include <vector>

namespace scrawble
{
    class config
    {
       public:
        config();

        typedef struct tile {
            int score;
            int count;
            char letter;
            tile(int score, int count, char letter) : score(score), count(count), letter(letter)
            {
            }
        } tile;

        const std::vector<tile> &tile_distributions() const;

        const std::string &dictionary_file_name() const;

        virtual void load(const std::string &filename) = 0;

       protected:
        std::vector<tile> letters_;
        std::string dictionary_;
    };
}

#endif
