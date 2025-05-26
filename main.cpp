#include "retrocs/retrocs.h"
#include "Game/scenes/DebugMap.h"

using namespace game;
using namespace game::ecs;

int main()
{
    DebugMap scene = DebugMap();
    VirtualScreen& screen = scene.screen_space;

    scene.enter();

    scene.update();

    debug(scene.get_at<Entity>(7, 2).id);

    scene.exit();


    return 0;
}

