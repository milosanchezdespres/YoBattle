#pragma once

#include "Window/Window.h"
#include "Utils/Utils.h"
//...

namespace retrocs
{
    namespace hub
    {
        inline GameWindow* game;

        inline void init()
        {
            game = new GameWindow();

            //...
        }
    }
}

using namespace retrocs;