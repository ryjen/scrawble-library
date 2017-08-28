#include "gaddag.h"

namespace scrawble
{
    const char Node::CROSS_ANCHOR_CHAR = '#';

    Direction Direction::inverse() const
    {
        if (xInc == 0) {
            return yInc == -1 ? DOWN : UP;
        } else {
            return xInc == -1 ? RIGHT : LEFT;
        }
    }

    Direction Direction::perpendicular() const
    {
        if (xInc == 0) {
            return RIGHT;
        } else {
            return DOWN;
        }
    }
}