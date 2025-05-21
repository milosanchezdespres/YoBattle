#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Components/Image.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct UIRenderSystem : public System<Image>
        {
            Vector2 __position, __origin;
            Rectangle __source, __destination;

            UIRenderSystem () : System<Image>() { }

            void OnDraw(Entity* owner, Image* component) override
            {
                owner->extra_events(Game::instance().delta());
                owner->extra_draw();
            }
        };
    }
}