#include <scrawble/vt100.h>

namespace vt100
{
    std::string color(int foreground, int attr, int background)
    {
        std::string buf(ESC);

        buf += "[";

        buf += std::to_string(attr);

        if (foreground != NONE) {
            buf += ";";
            buf += std::to_string(foreground + FOREGROUND);
        }

        if (background != NONE) {
            buf += ";";
            buf += std::to_string(background + BACKGROUND);
        }

        buf += "m";

        return buf;
    }

    std::string reset()
    {
        return std::string(ESC) + "[0m";
    }

    std::string clear()
    {
        return std::string(ESC) + "[2J";
    }
    namespace cursor
    {
        std::string set(int row, int col)
        {
            std::string buf(ESC);

            buf += "[";

            if (row != NONE) {
                buf += std::to_string(row);
            }

            if (col != NONE) {
                if (row != NONE) {
                    buf += ";";
                }
                buf += std::to_string(col);
            }
            buf += "H";
            return buf;
        }

        std::string save()
        {
            return std::string(ESC) + "[s";
        }

        std::string restore()
        {
            return std::string(ESC) + "[u";
        }

        std::string up(int amount)
        {
            std::string buf(ESC);

            buf += "[";
            buf += std::to_string(amount);
            buf += "A";
            return buf;
        }
        std::string down(int amount)
        {
            std::string buf(ESC);

            buf += "[";
            buf += std::to_string(amount);
            buf += "B";
            return buf;
        }
        std::string back(int amount)
        {
            std::string buf(ESC);

            buf += "[";
            buf += std::to_string(amount);
            buf += "D";
            return buf;
        }
        std::string forward(int amount)
        {
            std::string buf(ESC);

            buf += "[";
            buf += std::to_string(amount);
            buf += "C";
            return buf;
        }

    }  // namespace cursor
}  // namespace vt100