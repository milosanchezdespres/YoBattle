#pragma once

#include "../../Components/StateMachine.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct PlayerWalk : public State
        {
            PlayerWalk(Character* _owner) : State(_owner) {}

            void OnEnter() override
            {
                //...
            }

            void OnUpdate(float delta) override
            {
                //...

                //when finished
                //does<PlayerIdle>();
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}