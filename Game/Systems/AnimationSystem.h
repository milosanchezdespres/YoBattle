#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/Animations.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct AnimationSystem : public System<Animations>
        {
            AnimationSystem () : System<Animations>() { }

            void OnDraw(Entity* owner, Animations* component) override
            {
                //...
            }
        };
    }
}