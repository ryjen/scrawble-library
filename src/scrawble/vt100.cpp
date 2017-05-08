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
    }  // namespace cursor
}  // namespace vt100