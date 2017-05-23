#include <scrawble/game_logic.h>
#include <scrawble/lexicon/node.h>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>

namespace scrawble
{
    game_logic::game_logic()
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

    void game_logic::finish_turn()
    {
        if (++turn_ > players_.size()) {
            turn_ = 0;
        }
    }

    void game_logic::init(const config &conf)
    {
        init_dictionary(conf.dictionary_file_name());

        for (auto t : conf.tile_distributions()) {
            for (int i = 0; i < t.count; i++) {
                bag_.push(tile(t.letter, t.score));
            }
        }

        player &plr = players_[this_player_index];

        for (int i = 0; i < player::rack_size; i++) {
            plr.push(bag_.next());
        }
    }
}
