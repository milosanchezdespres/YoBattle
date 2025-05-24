#pragma once

#include "../../RetroCS/RetroCS.h"

namespace yokard
{
    namespace ecs
    {
        struct Sprite : public Component
        {
            float x, y;
            string texture;

            int tile_index;
            int tile_size;

            Sprite() : Component() { }

            void _on_init() override
            {
                x = 0;
                y = 0;

                texture = "";

                tile_index = -1;
                tile_size = 0;
            }

            void _on_raw_conversion() override
            {
                ___screen_data->x = x;
                ___screen_data->y = y;

                //if tile_index => -1 w => screen_width
                ___screen_data->w = tile_size;
                ___screen_data->h = tile_size;
            }

            //void _on_destroy() override {}
        };
    }
}
