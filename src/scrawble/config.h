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
            tile(int score, int count, const char &letter) : score(score), count(count), letter(letter)
            {
            }
        } tile;

        const std::vector<tile> &letters() const;

        const std::string &dictionary() const;

        virtual void load(const std::string &filepath) = 0;

       private:
        std::vector<tile> letters_;
        std::string dictionary_;
    };
}

#endif
