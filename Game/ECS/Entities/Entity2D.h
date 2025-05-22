#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Components/Image.h"
#include "../Components/Sprite.h"

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
                add<Sprite>();

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

                if(has("sprite"))
                {
                    x *= get<Image>()->scale;
                    y *= get<Image>()->scale;

                    int tiles_per_row = texture_width / get<Sprite>()->tile->size;

                    float source_width = get<Sprite>()->tile->size;
                    float source_height = get<Sprite>()->tile->size;

                    float source_x = (get<Sprite>()->tile->index % tiles_per_row) * source_width;
                    float source_y = (get<Sprite>()->tile->index / tiles_per_row) * source_height;

                    float destination_width = get<Image>()->scale * source_width;
                    float destination_height = get<Image>()->scale * source_height;

                    DrawTexturePro(
                        *game()->get<texture>(get<Image>()->texture)->data, 
                        {source_x, source_y, source_width, source_height}, 
                        {x, y, destination_width, destination_height}, 
                        {0, 0}, 
                        get<Image>()->rotation, 
                        WHITE
                    );
                }
                else
                {
                    DrawTexturePro(
                        *game()->get<texture>(get<Image>()->texture)->data,
                        {0 , 0, texture_width, texture_height},
                        {x, y, scaled_width, scaled_height},
                        {0, 0},
                        get<Image>()->rotation,
                        WHITE
                    );
                }
            }
        };
    }
}