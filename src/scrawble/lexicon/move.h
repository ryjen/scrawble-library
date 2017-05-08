#ifndef SCRAWBLE_LEXICON_MOVE_H
#define SCRAWBLE_LEXICON_MOVE_H

#include <array>
#include <vector>

class move
{
   private:
    typedef struct __point {
        int x;
        int y;
        __point(int x, int y) : x(x), y(y)
        {
        }
    } point;

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

   public:
    move(const point &start, const std::string &word) : start_(start), word_(word), score_(0)
    {
    }

    move &push(const data &value)
    {
        placed_.push_back(value);
        return *this;
    }
};

#endif
