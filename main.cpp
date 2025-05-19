#include "RetroCS/RetroCS.h"

int main()
{
    Game::instance().start("YoBattle");
    
    Game::instance().update();

    return 0;
}