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
    class GameLogic
    {
       public:
        static std::mt19937 random_generator;

        GameLogic();

        Player &player();

        const Player &player() const;

        Board &board();

        const Board &board() const;

        GameLogic &finish_turn(int score);

        virtual std::set<std::string> hints() const = 0;

        Bag &bag();

        GameLogic &init(const Config &conf);

        virtual void init_dictionary(const std::string &fileName) = 0;

       protected:
        Board board_;
        Bag bag_;
        std::vector<Player> players_;
        int turn_;

       private:
        static const int max_players = 4;
        static const int this_player_index = 0;
    };
}

#endif
