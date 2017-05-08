#ifndef SCRAWBLE_BOARD_H
#define SCRAWBLE_BOARD_H

#include <array>
#include <iostream>
#include <iterator>
#include <vector>

class board {
   public:
    const static int size = 15;

    board();

    void init();

    void print(std::ostream& out) const;

   private:
    void print_bonus_square(std::ostream& out, int bonus, int color) const;

    char values_[size][size];
    short wordBonus_[size][size];
    short letterBonus_[size][size];
};

#endif
