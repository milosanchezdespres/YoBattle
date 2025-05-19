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

        int width, height, tile_size;

        int scale;
        float rotation;
        int tile_index;

        Sprite() : Component()
        {
            visible = true;

            position.x = 0;
            position.y = 0;

            width = 0;
            height = 0;
            tile_size = 0;

            scale = 1;
            rotation = 0;

            tile_index = -1;
        }
    };
}