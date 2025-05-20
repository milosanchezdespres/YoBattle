#pragma once

#include "../../Components/StateMachine.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct PlayerWalk;
        
        struct PlayerIdle : public State
        {
            PlayerIdle(Entity* _owner) : State("idle", _owner) {}

            void OnEnter() override
            {
                //...
            }

            void OnUpdate(float delta) override
            {
                if(Game::instance().is_down("up"))
                {
                    owner()->get<StateMachine>("states")->axis = 0;
                    owner()->get<StateMachine>("states")->does<PlayerWalk>();
                }
                else if(Game::instance().is_down("down"))
                {
                    owner()->get<StateMachine>("states")->axis = 1;
                    owner()->get<StateMachine>("states")->does<PlayerWalk>();
                }
                else if(Game::instance().is_down("left"))
                {
                    owner()->get<StateMachine>("states")->axis = 2;
                    owner()->get<StateMachine>("states")->does<PlayerWalk>();
                }
                else if(Game::instance().is_down("right"))
                {
                    owner()->get<StateMachine>("states")->axis = 3;
                    owner()->get<StateMachine>("states")->does<PlayerWalk>();
                }
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}