#include "Game.hpp"
#include <time.h>

int main()
{
    srand((uint16_t)time(NULL));

    Game myGame;
    myGame.run();
}