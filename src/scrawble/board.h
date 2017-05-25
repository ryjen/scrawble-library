#ifndef SCRAWBLE_BOARD_H
#define SCRAWBLE_BOARD_H

#include <array>
#include <iostream>
#include <iterator>
#include <vector>

namespace scrawble
{
    class board
    {
       public:
        const static int size = 15;

        board();

        void init();

        char value(int x, int y);

        short bonus(int x, int y, bool word = false);

        void place(int x, int y, char letter);

        class row
        {
           public:
            row(char const value[size]);
            row(const row &other);
            row &operator=(const row &other);

            char operator[](int index) const;

           private:
            char values_[size];
        };

        row operator[](int index) const;

       private:
        char values_[size][size];
        short wordBonus_[size][size];
        short letterBonus_[size][size];
    };
}

#endif
