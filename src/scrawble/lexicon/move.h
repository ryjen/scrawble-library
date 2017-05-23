#ifndef SCRAWBLE_LEXICON_MOVE_H
#define SCRAWBLE_LEXICON_MOVE_H

#include <array>
#include <vector>

namespace lexicon
{
    typedef struct __point {
        int x;
        int y;
        __point(int x, int y) : x(x), y(y)
        {
        }
        __point() : x(0), y(0)
        {
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
        move(const point &start, const std::string &word, direction::type dir)
            : start_(start), word_(word), score_(0), direction_(dir)
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
    };
}

#endif
