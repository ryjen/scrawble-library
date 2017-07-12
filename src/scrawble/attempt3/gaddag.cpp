#include <scrawble/attempt3/gaddag.h>

namespace scrawble {
    Gaddag::Dir::Dir(int a, int b) : x(a), y(b) {
    }
    int Gaddag::Dir::nextX(int v) const {
        return v + x;
    }
    int Gaddag::Dir::nextY(int v) const {
        return v + y;
    }
    bool Gaddag::Dir::hasNext(const Board &board, int a, int b) const {
        return board.contains(nextX(a), nextY(b));
    }
    bool Gaddag::Dir::nextIsInBounds(int x, int y) {
        int nextX = nextX(x);
        int nextY = nextY(y);
        return (1 <= nextX && nextX <= Board::size) && (1 <= nextY && nextY <= Board::size);
    }
}  // namespace scrawble