#ifndef SCRAWBLE_LEXICON_MOVE_H
#define SCRAWBLE_LEXICON_MOVE_H

#include <array>
#include <vector>

namespace scrawble
{
    namespace lexicon
    {
        typedef struct __point {
            int x;
            int y;
            __point(int x, int y) : x(x), y(y)
            {
            }
            __point() : x(-1), y(-1)
            {
            }
            bool valid() const
            {
                return x >= 0 && y >= 0;
            }
            bool operator<(const struct __point &p) const
            {
                return x < p.x && y < p.y;
            }
        } point;

        namespace direction
        {
            typedef enum { left, right, up, down } type;
        }

        class move
        {
            std::string word_;
            lexicon::point start_;
            int score_;

           public:
            move(const point &start, const std::string &word, int score)
                : word_(word), start_(start), score_(score)
            {
            }

            bool operator<(const move &other) const
            {
                return word_ < other.word_;
            }

            const std::string &word() const
            {
                return word_;
            }

            point start() const
            {
                return start_;
            }

            int score() const
            {
                return score_;
            }
        };
    }
}
#endif
