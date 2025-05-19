#pragma once

#include <raylib.h>

#include "../../../ECS/ECS.h"


#include <cstdint>
using namespace std;

namespace YOBATTLE
{
    struct Animator : public Component
    {
        float time;
        float speed;

        Animator() : Component()
        {
            time = 0;
            speed = 15;
        }
    };
}