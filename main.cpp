#include "RetroCS/RetroCS.h"
#include "Game/scenes/DebugScene.h"

int main()
{
    hub::init<DebugScene>("YoKard");

    hub::update();

    return 0;
}