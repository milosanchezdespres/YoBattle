#pragma once

#include "../../Components/StateMachine.h"

namespace YoBattleGame
{
    namespace ECS
    {
        //struct NPCWalk;
        
        struct NPCIdle : public State
        {
            NPCIdle(Entity* _owner) : State("idle", _owner) {}

            void OnEnter() override
            {
                //...
            }

            void OnUpdate(float delta) override
            {
                //...
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}