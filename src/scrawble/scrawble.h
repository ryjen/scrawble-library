#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/board.h>
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

    void search(int x, int y, const std::vector<char> &rack, const std::set<move> &pool) const;

    scrawble();

    void print(std::ostream &out) const;

   private:
    static constexpr const char *DICTIONARY_FILE = "assets/dictionary.txt";

    int round_;
    gaddag dictionary_;
    board board_;
    std::array<player, max_players> players_;
    std::stack<move> history_;
    int turn_;
};

extern std::ostream &operator<<(std::ostream &out, const scrawble &scrawble);

#endif
