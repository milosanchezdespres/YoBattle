#include "includes.h"

#include "ECS/Game.h"

int main()
{
    Game::loop().Init(new CustomEntityFactory(), true);

    Game::loop().Update();

    return 0;
}