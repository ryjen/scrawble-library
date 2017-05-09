#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/bag.h>
#include <scrawble/board.h>
#include <scrawble/config.h>
#include <scrawble/io.h>
#include <scrawble/lexicon/gaddag.h>
#include <scrawble/lexicon/move.h>
#include <scrawble/player.h>
#include <scrawble/tile.h>
#include <set>
#include <stack>
#include <vector>

class scrawble
{
   public:
    static const int max_players = 4;

    void search(int x, int y, const std::vector<tile> &rack, const std::set<lexicon::move> &pool) const;

    scrawble();

    void load(const config &conf);

    void load(const std::string &filePath = config::DEFAULT_CONFIG_FILE);

    bool is_over() const;

    void update();

    void render();

    player &get_player();

    void finish_turn();

    void quit();

    board &get_board();

   private:
    static const int this_player_index = 0;

    typedef enum { Running, Stopped } state_type;

    gaddag dictionary_;
    bag bag_;
    board board_;
    terminal_io term_;
    std::vector<player> players_;
    std::stack<lexicon::move> history_;
    int turn_;
    state_type state_;
};

#endif
