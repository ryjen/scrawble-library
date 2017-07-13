#include <scrawble/game_logic.h>
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

    std::mt19937 GameLogic::random_generator(detail::rd());

    GameLogic::GameLogic() : players_(max_players)
    {
    }

    Player &GameLogic::player()
    {
        return players_[this_player_index];
    }

    const Player &GameLogic::player() const
    {
        return players_[this_player_index];
    }

    Board &GameLogic::board()
    {
        return board_;
    }

    Bag &GameLogic::bag()
    {
        return bag_;
    }

    GameLogic &GameLogic::finish_turn(int score)
    {
        players_[turn_].add_score(score);

        if (++turn_ > players_.size()) {
            turn_ = 0;
        }
        return *this;
    }

    GameLogic &GameLogic::init(const Config &conf)
    {
        init_dictionary(conf.dictionary_file_name());

        for (auto t : conf.tile_distributions()) {
            for (int i = 0; i < t.count; i++) {
                bag_.push(std::make_unique<Tile>(t.letter, t.score));
            }
        }
        return *this;
    }
}
