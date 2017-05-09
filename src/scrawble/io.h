#ifndef SCRAWBLE_INPUT_H
#define SCRAWBLE_INPUT_H

#include <scrawble/vt100.h>

class scrawble;
class player;

class io
{
   public:
    virtual void update(scrawble &game) = 0;
    virtual void render(scrawble &game) = 0;
};

/**
 * other inputs can be defined
 */
class terminal_io : public io
{
   public:
    terminal_io();
    virtual ~terminal_io();
    void update(scrawble &game);
    void render(scrawble &game);

   private:
    void render(board &board);
    void render(player &player);
    void render_help();
    void render_bonus_square(int bonus, int color) const;

    vt100::cursor::position pos_;
};

#endif
