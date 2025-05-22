#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Components/Animator.h"

namespace YoKard
{
    namespace ECS
    {
        struct AnimationSystem : public System<Animator>
        {
            void OnUpdate(Animator* component) override
            {
                //...

                debug("animating................................................................");
            }
        };
    }
}