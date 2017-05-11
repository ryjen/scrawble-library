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
    namespace algorithm
    {
        void search(int x, int y, const std::vector<tile> &rack, const std::set<lexicon::move> &pool);
    }
}

#endif
