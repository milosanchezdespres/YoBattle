#pragma once

#include <raylib.h>
#include "../../../ECS/ECS.h"

namespace YOBATTLE
{
    struct Sprite : public Component
    {
        Vector2 position;

        Sprite() : Component()
        {
            position.x = 0;
            position.y = 0;
        }
    };
}