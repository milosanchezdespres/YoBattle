#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/Image.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct ImageRenderSystem : public System<Image>
        {
            Vector2 __position, __origin;
            Rectangle __source, __destination;

            ImageRenderSystem () : System<Image>() { }

            void OnDraw(Entity* owner, Image* component) override
            {
                __position.x = component->x + (component->scale_h * 3);
                __position.y = component->y + (component->scale_v * 1.8f);

                DrawTexturePro(
                    Game::instance().texture(component->texture_alias),
                    { 0, 0, (float)Game::instance().texture(component->texture_alias).width, 
                            (float)Game::instance().texture(component->texture_alias).height },
                    { __position.x, __position.y, 
                    Game::instance().texture(component->texture_alias).width * component->scale_h, 
                    Game::instance().texture(component->texture_alias).height * component->scale_v },
                    { Game::instance().texture(component->texture_alias).width * 0.5f, 
                    Game::instance().texture(component->texture_alias).height * 0.5f },
                    component->r,
                    WHITE
                );
            }
        };
    }
}