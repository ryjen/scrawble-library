#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/bag.h>
#include <scrawble/board.h>
#include <scrawble/config.h>
#include <scrawble/lexicon/gaddag.h>
#include <scrawble/lexicon/move.h>
#include <scrawble/player.h>
#include <scrawble/tile.h>
#include <set>
#include <stack>
#include <vector>

namespace scrawble
{
    namespace temp
    {
        struct move {
            lexicon::point start;
            lexicon::point left;
            lexicon::point actual;
            lexicon::direction::type direction;
            std::string word;
            lexicon::node::ptr node;
            std::vector<tile> rack;

            move(const lexicon::point start, const lexicon::point &actual, lexicon::direction::type dir,
                 const std::string &word, const lexicon::node::ptr &node, const std::vector<tile> &rack);

            move copy(char del) const;

            move turn(lexicon::direction::type dir) const;

            lexicon::move convert() const;
        };
    }

    class game
    {
       public:
        game();

        void search(int x, int y, const std::vector<tile> &rack, std::set<lexicon::move> &pool);

        player &get_player();

        board &get_board();

        void finish_turn();

        virtual void load(const config &conf) = 0;

       protected:
        bag bag_;
        board board_;
        lexicon::gaddag dictionary_;
        std::vector<player> players_;
        int turn_;

       private:
        static const int this_player_index = 0;

        bool end_of_board(const temp::move &m) const;

        char next_tile(const temp::move &m) const;

        void recurse_left_right(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                                const std::vector<tile> &rack);

        void recurse_up_down(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                             const std::vector<tile> &rack);

        void search_recursive(std::set<lexicon::move> &pool, const temp::move &m);

        bool cross(const temp::move &m, char ch) const;

        bool contains(int x, int y, bool down, int x2, int y2, char ch) const;
    };
}

#endif
