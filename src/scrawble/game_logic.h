#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/bag.h>
#include <scrawble/board.h>
#include <scrawble/config.h>
#include <scrawble/player.h>
#include <random>
#include <set>
#include <vector>

namespace scrawble
{
    class game_logic
    {
       public:
        static std::mt19937 random_generator;

        game_logic();

        scrawble::player &player();

        const scrawble::player &player() const;

        scrawble::board &board();

        game_logic &finish_turn(int score);

        virtual std::set<std::string> hints() const = 0;

        scrawble::bag &bag();

        game_logic &init(const config &conf);

        virtual void init_dictionary(const std::string &fileName) = 0;

       protected:
        scrawble::board board_;
        scrawble::bag bag_;
        std::vector<scrawble::player> players_;
        int turn_;

       private:
        static const int max_players = 4;
        static const int this_player_index = 0;
    };
}

#endif
