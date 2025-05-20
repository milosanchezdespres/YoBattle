#pragma once

#include "../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Tile
        {
            uint8_t size;
            uint8_t index;
        };

        struct Sprite : public Component
        {
            string texture_alias;

            float x, y, r;

            Tile* tile;

            Sprite () : Component()
            {
                texture_alias = "";

                x = 0;
                y = 0;

                tile = new Tile();
                tile->size = 8;
                tile->index = 0;
            }
        };
    }
}
