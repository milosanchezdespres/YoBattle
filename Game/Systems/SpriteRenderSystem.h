#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/Sprite.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct SpriteRenderSystem : public System<Sprite>
        {
            SpriteRenderSystem () : System<Sprite>() { }

            void OnDraw(Entity* owner, Sprite* component) override
            {
                //...

                cout << "> " + component->alias << endl;
            }
        };
    }
}