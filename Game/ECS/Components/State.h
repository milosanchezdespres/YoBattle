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

        State() : Component()
        {
            direction = 1;
            //...
        }
    };
}