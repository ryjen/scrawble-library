#ifdef WIN32
#include <conio.h>
#else
#include <curses.h>
#endif
#include <scrawble/bag.h>
#include <scrawble/board.h>
#include <scrawble/game.h>
#include <cstdlib>

#define HIGHLIGHT 8

namespace scrawble
{
    terminal_io::terminal_io() : pos_(19, 31), flags_(FLAG_DIRTY)
    {
        timeout(-1);
        setlocale(LC_CTYPE, "");
        initscr();
        raw();
        noecho();
        start_color();

        init_pair(COLOR_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(COLOR_RED, COLOR_BLACK, COLOR_RED);
        init_pair(COLOR_GREEN, COLOR_BLACK, COLOR_GREEN);
        init_pair(COLOR_YELLOW, COLOR_BLACK, COLOR_YELLOW);
        init_pair(COLOR_CYAN, COLOR_BLACK, COLOR_CYAN);
        init_pair(COLOR_BLUE, COLOR_BLACK, COLOR_BLUE);
        init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
        init_pair(HIGHLIGHT, COLOR_BLACK, COLOR_WHITE);
    }

    terminal_io::~terminal_io()
    {
        clear();
    }

    void terminal_io::update(game &game)
    {
        switch (getch()) {
            case 'f':
                game.finish_turn();
                flags_ |= FLAG_DIRTY;
                break;
            case KEY_UP:
                pos_.y--;
                flags_ |= FLAG_DIRTY;
                break;
            case KEY_DOWN:
                pos_.y++;
                flags_ |= FLAG_DIRTY;
                break;
            case KEY_LEFT:
                pos_.x--;
                flags_ |= FLAG_DIRTY;
                break;
            case KEY_RIGHT:
                pos_.x++;
                flags_ |= FLAG_DIRTY;
                break;
            case 's':
                game.get_player().shuffle();
                flags_ |= FLAG_DIRTY;
                break;
            case 'q':
            case 'x':
                game.quit();
                break;
        }
    }

    void terminal_io::render(game &game)
    {
        if ((flags_ & FLAG_DIRTY) == 0) {
            return;
        }

        flags_ &= ~(FLAG_DIRTY);

        move(0, 0);

        render(game.get_board());

        render(game.get_player());

        render_help();

        render_select();
    }

    void terminal_io::render_help()
    {
        file_reader reader("assets/help.txt");

        int row = 2;
        for (auto line : reader) {
            move(row++, 66);
            printw("%s", line.c_str());
        }
    }

    void terminal_io::render_select()
    {
        move(pos_.x, pos_.y);
        chgat(1, A_BOLD, COLOR_PAIR(HIGHLIGHT), NULL);
    }

    void terminal_io::render(player &player)
    {
        printw("                ╭───┬───┬───┬───┬───┬───┬───╮\n");
        printw("                ");

        for (auto tile : player.rack()) {
            printw("│ ");
            attron(A_BOLD | COLOR_PAIR(COLOR_WHITE));
            printw("%c ", tile.letter());
            attroff(A_BOLD | COLOR_PAIR(COLOR_WHITE));
        }
        printw("│\n");

        printw("                ╰───┴───┴───┴───┴───┴───┴───╯\n");
    }

    void terminal_io::render(board &board)
    {
        for (int i = 0; i < board::size; i++) {
            if (i == 0) {
                printw("╭───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───╮\n");
            } else {
                printw("├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");
            }
            for (int j = 0; j < board::size; j++) {
                printw("│ ");
                if (board.value(i, j) == lexicon::node::EMPTY) {
                    switch (board.bonus(i, j, true)) {
                        case 2:
                            render_bonus_square(2, COLOR_MAGENTA);
                            break;
                        case 3:
                            render_bonus_square(3, COLOR_RED);
                            break;
                        default:
                            switch (board.bonus(i, j, false)) {
                                case 2:
                                    render_bonus_square(2, COLOR_CYAN);
                                    break;
                                case 3:
                                    render_bonus_square(3, COLOR_YELLOW);
                                    break;
                                default:
                                    printw(" ");
                                    break;
                            }
                    }
                } else {
                    attron(A_BOLD | COLOR_PAIR(COLOR_WHITE));
                    printw("%c", board.value(i, j));
                    attroff(A_BOLD | COLOR_PAIR(COLOR_WHITE));
                }
                printw(" ");
            }
            printw("│\n");
        }
        printw("╰───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───╯\n");
    }

    void terminal_io::render_bonus_square(int bonus, int color) const
    {
        attron(COLOR_PAIR(color));
        printw("%d", bonus);
        attroff(COLOR_PAIR(color));
    }
}
