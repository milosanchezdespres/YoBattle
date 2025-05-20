#include "Game/YoBattle.h"

int main()
{
    Game::instance().start<YoBattle>("YoBattle");
    
    Game::instance().update();

    return 0;
}