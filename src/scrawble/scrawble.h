#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/bag.h>
#include <scrawble/board.h>
#include <scrawble/config.h>
#include <scrawble/lexicon/gaddag.h>
#include <scrawble/lexicon/move.h>
#include <scrawble/player.h>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

class scrawble
{
   public:
    static const int max_players = 4;

    void search(int x, int y, const std::vector<char> &rack,
                const std::set<move> &pool) const;

    scrawble(const config &conf);

    void print(std::ostream &out) const;

   private:
    static const int this_player = 0;

    int round_;
    gaddag dictionary_;
    bag bag_;
    board board_;
    std::array<std::shared_ptr<player>, max_players> players_;
    std::stack<move> history_;
    int turn_;
};

extern std::ostream &operator<<(std::ostream &out, const scrawble &scrawble);

#endif
