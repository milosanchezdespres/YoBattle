#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Character.h"
#include "../Components/StateHolder.h"

namespace YoKard
{
    namespace ECS
    {
        struct StateMachine : public System<StateHolder>
        {
            bool inbound;

            void OnUpdate(StateHolder* component) override
            {
                inbound = component->owner<Entity2D>()->get<Image>()->in_bound;

                if(inbound)
                {
                    if(component->state == nullptr) component->go_to_entry_point();

                    component->state->update();
                }
            }
        };
    }
}