#pragma once

#include "../../Components/StateMachine.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct PlayerIdle : public State
        {
            PlayerIdle(Character* _owner) : State(_owner) {}

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