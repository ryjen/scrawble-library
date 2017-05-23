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

        void initialize();

        char value(int x, int y);

        short bonus(int x, int y, bool word = false);

        class row
        {
           public:
            row(char const value[size]);

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
