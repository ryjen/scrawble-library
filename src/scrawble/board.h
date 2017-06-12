#ifndef SCRAWBLE_BOARD_H
#define SCRAWBLE_BOARD_H

#include <scrawble/tile.h>
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

        board(const board &other);
        board(board &&other);

        board &operator=(const board &other);
        board &operator=(board &&other);

        virtual ~board();

        tile &value(int x, int y);

        short bonus(int x, int y, bool word = false);

        tile place(int x, int y, const tile &value);

        board &reset(int x, int y);

        class row
        {
           public:
            row(tile const value[size]);
            row(const row &other);
            row &operator=(const row &other);

            tile operator[](int index) const;

           private:
            tile values_[size];
        };

        row operator[](int index) const;

       private:
        void init();
        void copy(const board &from);
        tile values_[size][size];
        short wordBonus_[size][size];
        short letterBonus_[size][size];
    };
}

#endif
