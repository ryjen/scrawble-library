#ifndef SCRAWBLE_GAME_H
#define SCRAWBLE_GAME_H

#include <curses.h>
#include <scrawble/config.h>
#include <scrawble/io.h>
#include <scrawble/player.h>
#include <scrawble/scrawble.h>
#include <scrawble/tile.h>

namespace scrawble
{
    class game : public scrawble
    {
       public:
        static const int max_players = 4;

        game(const config& conf) : turn_(0), players_(max_players), state_(Running)
        {
            load(conf);
        }

        ~game()
        {
            endwin();
        }

        void load(const config& conf)
        {
            file_reader reader(conf.dictionary());

            for (auto line : reader) {
                dictionary_.push(line);
            }

            for (auto t : conf.letters()) {
                for (int i = 0; i < t.count; i++) {
                    bag_.push(tile(t.letter, t.score));
                }
            }

            player& plr = players_[this_player_index];

            for (int i = 0; i < player::rack_size; i++) {
                plr.push(bag_.next());
            }
        }

        void update()
        {
            term_.update(*this);
        }

        void render()
        {
            term_.render(*this);
        }

        player& get_player()
        {
            return players_[this_player_index];
        }

        board& get_board()
        {
            return board_;
        }

        void finish_turn()
        {
            if (++turn_ > players_.size()) {
                turn_ = 0;
            }
        }

        void quit()
        {
            state_ = Stopped;
        }

        bool is_over() const
        {
            return state_ == Stopped;
        }

       private:
        static const int this_player_index = 0;

        typedef enum { Running, Stopped } state_type;

        terminal_io term_;
        std::vector<player> players_;
        int turn_;
        state_type state_;
    };
}

#endif
