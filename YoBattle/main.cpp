#include "Game/Game_includes.h"

int main()
{
    Game* game = new Game("YoBattle");

    game->Update();

    return 0;
}