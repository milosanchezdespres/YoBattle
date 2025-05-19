#pragma once

#include <raylib.h>
#include "../../../ECS/ECS.h"

namespace YOBATTLE
{
    struct Sprite : public Component
    {
        bool visible;

        string texture;
        Vector2 position;
        Vector2 size;

        int scale;
        float rotation;

        Sprite() : Component()
        {
            visible = true;

            position.x = 0;
            position.y = 0;

            size.x = 0;
            size.y = 0;

            scale = 1;
            rotation = 0;
        }
    };
}