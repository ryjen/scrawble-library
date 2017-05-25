#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/algorithm.h>
#include <scrawble/bag.h>
#include <scrawble/config.h>
#include <scrawble/player.h>
#include <vector>

namespace scrawble
{
    class game_logic : public algorithm
    {
       public:
        game_logic();

        player &get_player();

        board &get_board();

        bag &get_bag();

        void finish_turn();

        void init(const config &conf);

       protected:
        bag bag_;
        std::vector<player> players_;
        int turn_;

       private:
        static const int max_players = 4;
        static const int this_player_index = 0;
    };
}

#endif
