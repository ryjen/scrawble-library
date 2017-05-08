#include <scrawble/scrawble.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
    config config;

    scrawble scrawble(config);

    std::cout << scrawble << std::endl;

    return EXIT_SUCCESS;
}