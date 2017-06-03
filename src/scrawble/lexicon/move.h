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
        } point;

        namespace direction
        {
            typedef enum { left, right, up, down } type;
        }

        class move
        {
            typedef struct __data {
                char c;
                point p;
                __data(char c, const point &p) : c(c), p(p)
                {
                }
            } data;

            point start_;
            std::string word_;
            int score_;
            std::vector<data> placed_;
            direction::type direction_;

           public:
            move(const point &start, const std::string &word, direction::type dir, int score)
                : start_(start), word_(word), score_(score), direction_(dir)
            {
            }

            move &push(const data &value)
            {
                placed_.push_back(value);
                return *this;
            }

            bool operator<(const move &other) const
            {
                return word_ < other.word_;
            }

            const std::string &get_word() const
            {
                return word_;
            }

            const point &get_point() const
            {
                return start_;
            }

            const int get_score() const
            {
                return score_;
            }
        };
    }
}
#endif
