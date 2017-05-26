#include <scrawble/game_logic.h>
#include <scrawble/lexicon/node.h>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>

namespace scrawble
{
    game_logic::game_logic() : players_(max_players)
    {
    }

    player &game_logic::get_player()
    {
        return players_[this_player_index];
    }

    board &game_logic::get_board()
    {
        return board_;
    }

    bag &game_logic::get_bag()
    {
        return bag_;
    }

    game_logic &game_logic::finish_turn()
    {
        if (++turn_ > players_.size()) {
            turn_ = 0;
        }
        return *this;
    }

    game_logic &game_logic::init(const config &conf)
    {
        init_dictionary(conf.dictionary_file_name());

        for (auto t : conf.tile_distributions()) {
            for (int i = 0; i < t.count; i++) {
                bag_.push(tile(t.letter, t.score));
            }
        }

        player &plr = players_[this_player_index];

        for (int i = 0; i < rack::size; i++) {
            plr.push(bag_.next());
        }

        return *this;
    }
}
