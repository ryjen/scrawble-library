#ifndef SCRAWBLE_GADDAG_H
#define SCRAWBLE_GADDAG_H

#include <scrawble/attempt3/algorithm.h>
#include <scrawble/board.h>

namespace scrawble {
    class Gaddag : public Algorithm {
       public:
        typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

        static Direction InverseDirection[];
        static Direction PerpendicularDirection[];

        Gaddag();
        Gaddag(const TrieFactory &factory);

       private:
        void init(const TrieFactory &factory);
        typedef struct Dir {
            int x;
            int y;
            Dir(int a, int b);
            int nextX(int v) const;
            int nextY(int v) const;
            bool hasNext(const Board &board, int a, int b) const;
            bool nextIsInBounds(int x, int y) const;
        } Dir;

        Trie trie_;
    };
}  // namespace scrawble

#endif
