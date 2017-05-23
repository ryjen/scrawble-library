#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif
#include <scrawble/bag.h>
#include <scrawble/board.h>
#include <scrawble/game.h>
#include <cstdlib>

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27

namespace scrawble
{
    terminal_io::terminal_io()
    {
        timeout(-1);
    }

    terminal_io::~terminal_io()
    {
        std::cout << vt100::clear();
    }

    void terminal_io::update(game &game)
    {
        switch (getch()) {
            case 'f':
                game.finish_turn();
                break;
            case KB_UP:
                pos_.y--;
                break;
            case KB_DOWN:
                pos_.y++;
                break;
            case KB_LEFT:
                pos_.x--;
                break;
            case KB_RIGHT:
                pos_.x++;
                break;
            case 's':
                game.get_player().shuffle();
                break;
            case 'q':
            case KB_ESCAPE:
                game.quit();
                break;
        }
    }

    void terminal_io::render(game &game)
    {
        std::cout << vt100::cursor::set(1, 1) << vt100::clear();

        render(game.get_board());

        render(game.get_player());

        render_help();
    }

    void terminal_io::render_help()
    {
        file_reader reader("assets/help.txt");

        int row = 2;
        for (auto line : reader) {
            std::cout << vt100::cursor::set(row++, 66);
            std::cout << line;
        }
    }

    void terminal_io::render(player &player)
    {
        std::cout << "                ╭───┬───┬───┬───┬───┬───┬───╮\n";
        std::cout << "                ";

        for (auto tile : player.rack()) {
            std::cout << "│ " << vt100::color(vt100::WHITE, vt100::BRIGHT) << tile.letter() << vt100::reset() << " ";
        }
        std::cout << "│\n";

        std::cout << "                ╰───┴───┴───┴───┴───┴───┴───╯\n";
    }

    void terminal_io::render(board &board)
    {
        for (int i = 0; i < board::size; i++) {
            if (i == 0) {
                std::cout << "╭───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───╮\n";
            } else {
                std::cout << "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n";
            }
            for (int j = 0; j < board::size; j++) {
                std::cout << "│ ";
                if (board.value(i, j) == '_') {
                    switch (board.bonus(i, j, true)) {
                        case 2:
                            render_bonus_square(2, vt100::MAGENTA);
                            break;
                        case 3:
                            render_bonus_square(3, vt100::RED);
                            break;
                        default:
                            switch (board.bonus(i, j, false)) {
                                case 2:
                                    render_bonus_square(2, vt100::CYAN);
                                    break;
                                case 3:
                                    render_bonus_square(3, vt100::YELLOW);
                                    break;
                                default:
                                    std::cout << " ";
                                    break;
                            }
                    }
                } else {
                    std::cout << vt100::color(vt100::WHITE, vt100::BRIGHT) << board.value(i, j) << vt100::reset();
                }
                std::cout << " ";
            }
            std::cout << "│\n";
        }
        std::cout << "╰───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───╯\n";
    }

    void terminal_io::render_bonus_square(int bonus, int color) const
    {
        std::cout << vt100::color(vt100::BLACK, vt100::RESET, color);

        std::cout << bonus << vt100::reset();
    }
}
