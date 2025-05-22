#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Components/Image.h"

namespace YoKard
{
    namespace ECS
    {
        struct Entity2D : public Entity
        {
            Entity2D() : Entity() {}

            void init() override
            {
                add<Image>();

                //...
            }

            void render() override
            {
                float x = (int) get<Image>()->x;
                float y = (int) get<Image>()->y;

                float texture_width = game()->get<texture>(get<Image>()->texture)->data->width;
                float texture_height = game()->get<texture>(get<Image>()->texture)->data->height;

                float scaled_width = texture_width * get<Image>()->scale;
                float scaled_height = texture_height * get<Image>()->scale;

                DrawTexturePro(
                    *game()->get<texture>(get<Image>()->texture)->data,
                    {0 , 0, texture_width, texture_height},
                    {x, y, scaled_width, scaled_height},
                    {0, 0},
                    get<Image>()->rotation,
                    WHITE
                );
            }
        };
    }
}