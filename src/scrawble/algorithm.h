#ifndef SCRAWBLE_ALGORITHM_H
#define SCRAWBLE_ALGORITHM_H

#include <scrawble/board.h>
#include <scrawble/lexicon/gaddag.h>
#include <scrawble/lexicon/move.h>
#include <scrawble/rack.h>
#include <scrawble/tile.h>
#include <set>
#include <stack>

namespace scrawble
{
    namespace temp
    {
        typedef struct move move;
    }

    class algorithm
    {
       public:
        algorithm();

        void search(int x, int y, const rack &rack, std::set<lexicon::move> &pool);

       protected:
        board board_;
        lexicon::gaddag dictionary_;

        virtual void init_dictionary(const std::string &fileName) = 0;

       private:
        bool end_of_board(const temp::move &m) const;

        tile next_tile(const temp::move &m) const;

        void recurse_left_right(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y, const rack &rack);

        void recurse_up_down(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y, const rack &rack);

        void search_recursive(std::set<lexicon::move> &pool, const temp::move &m);

        bool cross(const temp::move &m, char ch) const;

        bool contains(int x, int y, bool down, int x2, int y2, char ch) const;
    };
}

#endif
