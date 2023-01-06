#include "GameEngine/Game.h"
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 4)
    throw std::runtime_error("Need three arguments - "
                             "number of sheep, number of wolves, "
                             "simulation time\n");
    init_sdl();

    int retval = Game(std::stoul(argv[1]), std::stoul(argv[2])).loop(std::stoul(argv[3]));

    close_sdl();
    return retval;
}