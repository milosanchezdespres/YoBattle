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
                strcpy(___screen_data->texture, texture.c_str());

                ___screen_data->x = x;
                ___screen_data->y = y;

                ___screen_data->w = tile_size;
                ___screen_data->h = tile_size;

                if(tile_index == -1)
                {
                    ___screen_data->w = hub::data->get<::texture>(texture)->data->width;
                    ___screen_data->h = hub::data->get<::texture>(texture)->data->height;

                    //.....
                }
            }

            //void _on_destroy() override {}
        };
    }
}
