#pragma once

#include <raylib.h>

#include "../../../ECS/ECS.h"


#include <cstdint>
using namespace std;

namespace YOBATTLE
{
    struct State : public Component
    {
        uint8_t direction;
        string action;

        State() : Component()
        {
            direction = 0;
            action = "idle";
            //...
        }
    };
}