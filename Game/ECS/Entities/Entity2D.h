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

            void OnInit() override
            {
                add_tile("", "");

                //...
            }

            virtual void add_tile(string image_alias, string sprite_alias)
            {
                add<Image>(image_alias);
                add<Sprite>(sprite_alias);
            }

            virtual void add_tile(string texture_name, int tile_index, string image_alias, string sprite_alias, int tile_size, int scale, int rotation)
            {
                add_tile(image_alias, sprite_alias);

                get<Image>(image_alias)->texture = texture_name;
                get<Image>(image_alias)->scale = scale;
                get<Image>(image_alias)->rotation = rotation;

                get<Sprite>(sprite_alias)->tile->index = tile_index;
                get<Sprite>(sprite_alias)->tile->size = tile_size;
            }

            void render() override
            {
                if(has("sprite")) { __render_sprite("image", "sprite"); }
                else { __render_image("image"); }
            }

            virtual void __render_image(string image_alias)
            {
                float x = (int) get<Image>(image_alias)->x;
                float y = (int) get<Image>(image_alias)->y;

                float texture_width = game()->get<texture>(get<Image>(image_alias)->texture)->data->width;
                float texture_height = game()->get<texture>(get<Image>(image_alias)->texture)->data->height;

                float scaled_width = texture_width * camera().zoom  * get<Image>(image_alias)->scale;
                float scaled_height = texture_height * camera().zoom  * get<Image>(image_alias)->scale;

                if(camera().is_within_bounds(x, y, scaled_width, scaled_height))
                {
                    DrawTexturePro(
                        *game()->get<texture>(get<Image>(image_alias)->texture)->data,
                        {0 , 0, texture_width, texture_height},
                        {x, y, scaled_width, scaled_height},
                        {0, 0},
                        get<Image>(image_alias)->rotation,
                        WHITE
                    );
                }
            }

            virtual void __render_sprite(string image_alias, string sprite_alias)
            {
                float texture_width = game()->get<texture>(get<Image>(image_alias)->texture)->data->width;
                int tiles_per_row = texture_width / get<Sprite>(sprite_alias)->tile->size;

                float source_width = get<Sprite>(sprite_alias)->tile->size;
                float source_height = get<Sprite>(sprite_alias)->tile->size;

                float destination_width = get<Image>(image_alias)->scale * camera().zoom * source_width;
                float destination_height = get<Image>(image_alias)->scale * camera().zoom * source_height;

                float x = (int) camera().world_to_screen(get<Image>(image_alias)->x, get<Image>(image_alias)->y).x - destination_width / 2;
                float y = (int) camera().world_to_screen(get<Image>(image_alias)->x, get<Image>(image_alias)->y).y - destination_height / 2;

                float source_x = (get<Sprite>(sprite_alias)->tile->index % tiles_per_row) * source_width;
                float source_y = (get<Sprite>(sprite_alias)->tile->index / tiles_per_row) * source_height;

                get<Image>(image_alias)->in_bound = camera().is_within_bounds(x, y, destination_width, destination_height);

                if(camera().is_within_bounds(x, y, destination_width, destination_height))
                {
                    DrawTexturePro(
                        *game()->get<texture>(get<Image>(image_alias)->texture)->data, 
                        {source_x, source_y, source_width, source_height}, 
                        {x, y, destination_width, destination_height}, 
                        { destination_width / 2, destination_height / 2 }, 
                        get<Image>(image_alias)->rotation, 
                        WHITE
                    );

                    if(display_draw_count) draw_count++;
                }
            }
        };
    }
}