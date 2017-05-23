#include <scrawble/game.h>
#include <scrawble/scrawble.h>
#include <cstdio>

int main(int argc, char *argv[])
{
    scrawble::config config;

    std::cout << "Loading, please wait...\n";

    config.load();

    scrawble::game game(config);

    do {
        game.render();

        game.update();
    } while (!game.is_over());

    return EXIT_SUCCESS;
}