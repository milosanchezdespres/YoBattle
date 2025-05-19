#include "Game/YoBattle.h"
using namespace YoBattleGame::GameWindow;

int main()
{
    Game::instance().start<YoBattle>("YoBattle");
    
    Game::instance().update();

    return 0;
}