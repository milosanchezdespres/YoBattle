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
                __source.x = 0;
                __source.y = 0;
                __source.width = Game::instance().texture(sprite->texture).width;
                __source.height = Game::instance().texture(sprite->texture).height;

                if(sprite->tile_index < 0)
                { DrawTextureEx(Game::instance().texture(sprite->texture), sprite->position, sprite->rotation, sprite->scale, WHITE); }
                else
                {
                    __source.x = sprite->tile_index % (int)((__source.width / sprite->tile_size));
                    __source.y = sprite->tile_index / (__source.height / sprite->tile_size);
                    __source.width = sprite->scale * sprite->tile_size;
                    __source.height = sprite->scale * sprite->tile_size;

                    __destination.x = sprite->position.x;
                    __destination.y = sprite->position.y;
                    __destination.width = sprite->tile_size;
                    __destination.height = sprite->tile_size;

                    __origin.x = __source.width / 2.0f;
                    __origin.y = __source.height / 2.0f;

                    DrawTexturePro(Game::instance().texture(sprite->texture), __source, __destination, __origin, sprite->rotation, WHITE);
                }
            }
        }
    };
}