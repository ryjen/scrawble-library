#ifndef SCRAWBLE_VT100_H
#define SCRAWBLE_VT100_H

#include <string>

namespace vt100
{
    static constexpr const char* ESC = "\x1B";

    typedef enum {
        NONE = -1,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    } colors;

    typedef enum {
        RESET,
        BRIGHT,
        DIM,
        UNDERSCORE,
        BLINK,
        REVERSE,
        HIDDEN
    } attrs;

    typedef enum { FOREGROUND = 30, BACKGROUND = 40 } modifiers;

    std::string color(int foreground, int attr = RESET, int background = NONE);

    std::string reset();

    namespace cursor
    {
        std::string set(int row = NONE, int col = NONE);
        std::string save();
        std::string restore();
    }  // namespace cursor
}  // namespace vt100

#endif
