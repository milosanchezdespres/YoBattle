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
                                
                __destination.x = __position.x * Game::instance().camera()->zoom - Game::instance().camera()->x;
                __destination.y = __position.y * Game::instance().camera()->zoom - Game::instance().camera()->y;
                __destination.width = Game::instance().camera()->zoom * component->tile->size;
                __destination.height = Game::instance().camera()->zoom * component->tile->size;

                if(!Game::instance().camera()->out_of_screen(__destination.x, __destination.y, component->tile->size, Game::instance().width, Game::instance().height))
                    { DrawTexturePro(Game::instance().texture(component->texture_alias), __source, __destination, __origin, component->r, WHITE); }
            }
        };
    }
}