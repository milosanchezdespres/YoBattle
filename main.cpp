#include "Game/EntryPoint.h"

int main()
{
    GameWindow::instance().start<DebugMap>("Yokards");

    GameWindow::instance().update();

    return 0;
}