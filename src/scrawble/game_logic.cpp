#include <scrawble/game_logic.h>
#include <scrawble/lexicon/node.h>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>

namespace scrawble
{
    namespace detail
    {
        std::random_device rd;
    }
    std::mt19937 game_logic::random_generator(detail::rd());

    game_logic::game_logic() : players_(max_players)
    {
    }

    scrawble::player &game_logic::player()
    {
        return players_[this_player_index];
    }

    const scrawble::player &game_logic::player() const
    {
        return players_[this_player_index];
    }

    scrawble::board &game_logic::board()
    {
        return board_;
    }

    scrawble::bag &game_logic::bag()
    {
        return bag_;
    }

    game_logic &game_logic::finish_turn(int score)
    {
        players_[turn_].add_score(score);

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
        return *this;
    }

    std::set<lexicon::move> game_logic::hints() const
    {
        std::set<lexicon::move> pool;

        for (int x = 0; x < board::size; x++) {
            for (int y = 0; y < board::size; y++) {
                if (!board_[x][y].empty()) {
                    search(x, y, player().rack(), pool);
                }
            }
        }

        return pool;
    }
}
