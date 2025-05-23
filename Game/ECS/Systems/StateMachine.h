#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Entity2D.h"
#include "../Components/StateHolder.h"

namespace YoKard
{
    namespace ECS
    {
        struct StateMachine : public System<StateHolder>
        {
            void OnUpdate(StateHolder* component) override
            {
                if(component->owner<Entity2D>()->get<Image>()->in_bound)
                {
                    //...
                }
            }
        };
    }
}