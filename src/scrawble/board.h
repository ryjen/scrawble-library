#ifndef SCRAWBLE_BOARD_H
#define SCRAWBLE_BOARD_H

#include <scrawble/tile.h>
#include <array>
#include <iostream>
#include <iterator>
#include <vector>

namespace scrawble
{
    class Board
    {
       public:
        const static int size = 15;

        Board();

        Board(const Board &other);
        Board(Board &&other);

        Board &operator=(const Board &other);
        Board &operator=(Board &&other);

        virtual ~Board();

        Tile &value(int x, int y);

        short bonus(int x, int y, bool word = false);

        Tile place(int x, int y, const Tile &value);

        Board &reset(int x, int y);

        class Row
        {
           public:
            Row(Tile const value[size]);
            Row(const Row &other);
            Row &operator=(const Row &other);

            Tile operator[](int index) const;

           private:
            Tile values_[size];
        };

        Row operator[](int index) const;

       private:
        void init();
        void copy(const Board &from);
        Tile values_[size][size];
        short wordBonus_[size][size];
        short letterBonus_[size][size];
    };
}

#endif
