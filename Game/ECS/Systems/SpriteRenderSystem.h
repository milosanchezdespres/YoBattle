#pragma once

#include "../../../ECS/ECS.h"
#include "../Components/Sprite.h"

namespace YOBATTLE
{
    struct SpriteRenderSystem : System<Sprite>
    {
		Vector2 __position, __origin;
		Rectangle __source, __destination;

        SpriteRenderSystem() : System()
        {
            standalone = true;

            __position = Vector2();
            __source = Rectangle();
            __destination = Rectangle();
            __origin = Vector2();
        }

        void OnUpdate(float delta, Component* _component) override
        {
            Sprite* sprite = cast(_component);

            if(sprite->visible && Game::instance().is_texture_loaded(sprite->texture))
            {
                if(sprite->tile_index < 0)
                {
                    if(sprite->width > 0 && sprite->height > 0)
                    {
                        __source.x = 0;
                        __source.y = 0;
                        __source.width = sprite->scale * sprite->width;
                        __source.height = sprite->scale * sprite->height;

                        __destination.x = sprite->position.x;
                        __destination.y = sprite->position.y;
                        __destination.width = sprite->width;
                        __destination.height = sprite->height;

                        DrawTexturePro(Game::instance().texture(sprite->texture), __source, __destination, __origin, sprite->rotation, WHITE);
                    }
                    else
                    { DrawTextureEx(Game::instance().texture(sprite->texture), sprite->position, sprite->rotation, sprite->scale, WHITE); }
                }
                else
                {
                    int tiles_per_row = Game::instance().texture(sprite->texture).width / sprite->tile_size;

                    __source.x = (sprite->tile_index % tiles_per_row) * sprite->tile_size;
                    __source.y = (sprite->tile_index / tiles_per_row) * sprite->tile_size;
                    __source.width = sprite->tile_size;
                    __source.height = sprite->tile_size;

                    __destination.x = sprite->position.x;
                    __destination.y = sprite->position.y;
                    __destination.width = sprite->scale * sprite->tile_size;
                    __destination.height = sprite->scale * sprite->tile_size;

                    __origin.x = __source.width / 2.0f;
                    __origin.y = __source.height / 2.0f;

                    DrawTexturePro(Game::instance().texture(sprite->texture), __source, __destination, __origin, sprite->rotation, WHITE);
                }
            }
        }
    };
}