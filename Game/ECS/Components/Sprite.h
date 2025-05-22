#pragma once

#include "../../../RetroCS/RetroCS.h"

namespace YoKard
{
    namespace ECS
    {
        struct Tile
        {
            int index;
            int size;

            Tile()
            {
                index = 0;
                size = 16;
            }
        };
        
        struct Sprite : public Component
        {
            Tile* tile = new Tile();

            Sprite() : Component() {}
        };
    }
}