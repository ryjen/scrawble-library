#include <scrawble/scrawble.h>
#include <cstdio>

int main(int argc, char *argv[])
{
    scrawble game;

    game.load();

    do {
        game.render();

        game.update();
    } while (!game.is_over());

    return EXIT_SUCCESS;
}