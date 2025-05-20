#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/StateMachine.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct StateMachineSystem : public System<StateMachine>
        {
            StateMachineSystem () : System<StateMachine>() { }

            void OnDraw(Entity* owner, StateMachine* component) override
            {
                component->update(Game::instance().delta());
            }
        };
    }
}