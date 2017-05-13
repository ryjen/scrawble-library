#ifndef SCRAWBLE_SCRAWBLE_H
#define SCRAWBLE_SCRAWBLE_H

#include <scrawble/bag.h>
#include <scrawble/board.h>
#include <scrawble/lexicon/gaddag.h>
#include <scrawble/lexicon/move.h>
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
        };
    }

    class scrawble
    {
       public:
        void search(int x, int y, const std::vector<tile> &rack, const std::set<lexicon::move> &pool);

       private:
        void recurse_left_right(const std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                                const std::vector<tile> &rack);

        void recurse_up_down(const std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                             const std::vector<tile> &rack);

        void search_recursive(const std::set<lexicon::move> &pool, const temp::move &m);

        bag bag_;
        board board_;
        lexicon::gaddag dictionary_;
    };
}

#endif
