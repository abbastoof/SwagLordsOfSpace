#include "Game.h"
#include <time.h>

int main() {

	srand(static_cast<unsigned>(time(0))); // This is for the random number generator for the enemy spawn.
    Game game;

    game.run();

    return 0;
}