#include <scrawble/game.h>
#include <scrawble/scrawble.h>
#include <cstdio>

int main(int argc, char *argv[])
{
    scrawble::config config;

    config.load();

    scrawble::game handler(config);

    do {
        handler.render();

        handler.update();
    } while (!handler.is_over());

    return EXIT_SUCCESS;
}