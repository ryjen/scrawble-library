#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/algorithm.h>
#include <scrawble/bag.h>
#include <scrawble/config.h>
#include <scrawble/player.h>
#include <random>
#include <vector>

namespace scrawble
{
    class game_logic : public algorithm
    {
       public:
        static std::mt19937 random_generator;

        game_logic();

        scrawble::player &player();

        const scrawble::player &player() const;

        scrawble::board &board();

        game_logic &finish_turn(int score);

        std::set<lexicon::move> hints() const;

        scrawble::bag &bag();

        game_logic &init(const config &conf);

       protected:
        scrawble::bag bag_;
        std::vector<scrawble::player> players_;
        int turn_;

       private:
        static const int max_players = 4;
        static const int this_player_index = 0;
    };
}

#endif
