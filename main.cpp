#include "Game/YoBattle.h"
using namespace YOBATTLE;

int main()
{
    Game::instance().start(new YoBattle(), "YoBattle");

    Game::instance().update();

    return 0;
}