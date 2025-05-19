#pragma once

#include "../../../ECS/ECS.h"
#include "../Components/Sprite.h"

namespace YOBATTLE
{
    struct SpriteRenderSystem : System<Sprite>
    {
		Vector2 __position;
		Rectangle __source;

        SpriteRenderSystem() : System()
        {
            standalone = true;

            __position = Vector2();
            __source = Rectangle();
        }

        void OnUpdate(float delta, Component* _component) override
        {
            Sprite* sprite = cast(_component);

            if(sprite->visible && Game::instance().is_texture_loaded(sprite->texture))
            {
                __source.x = 0;
                __source.y = 0;
                __source.width = sprite->size.x;
                __source.height = sprite->size.y;

                //DrawTextureRec(Game::instance().texture(sprite->texture), __source, sprite->position, WHITE);
                DrawTextureEx(Game::instance().texture(sprite->texture), sprite->position, sprite->rotation, sprite->scale, WHITE);
            }
        }
    };
}