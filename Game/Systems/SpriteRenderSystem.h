#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/Sprite.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct SpriteRenderSystem : public System<Sprite>
        {
            Vector2 __position, __origin;
            Rectangle __source, __destination;

            SpriteRenderSystem () : System<Sprite>() { }

            void OnDraw(Entity* owner, Sprite* component) override
            {
                int tiles_per_row = Game::instance().texture(component->texture_alias).width / component->tile->size;

                __position.x = component->x;
                __position.y = component->y;

                __source.x = (component->tile->index % tiles_per_row) * component->tile->size;
                __source.y = (component->tile->index / tiles_per_row) * component->tile->size;
                __source.width = component->tile->size;
                __source.height = component->tile->size;

                __destination.x = Game::instance().camera()->zoom * __position.x;
                __destination.y = Game::instance().camera()->zoom * __position.y;
                __destination.width = Game::instance().camera()->zoom * component->tile->size;
                __destination.height = Game::instance().camera()->zoom * component->tile->size;

                DrawTexturePro(Game::instance().texture(component->texture_alias), __source, __destination, __origin, component->r, WHITE);
            }
        };
    }
}