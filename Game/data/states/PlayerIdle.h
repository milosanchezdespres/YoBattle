#pragma once

#include "../../Components/StateMachine.h"

#include "PlayerWalk.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct PlayerIdle : public State
        {
            PlayerIdle(Entity* _owner) : State("idle", _owner) {}

            void OnEnter() override
            {
                owner()->get<Sprite>("body")->tile->index = 
                    owner()->get<Animations>("anim")->animation("idle", owner()->get<StateMachine>("states")->axis)->frames[0];
            }

            void OnUpdate(float delta) override
            {
                if(Game::instance().is_down("up"))
                {
                    owner()->get<StateMachine>("states")->axis = 0;
                    owner()->get<StateMachine>("states")->does<PlayerWalk>();
                }
                if(Game::instance().is_down("down"))
                {
                    owner()->get<StateMachine>("states")->axis = 1;
                    owner()->get<StateMachine>("states")->does<PlayerWalk>();
                }
                if(Game::instance().is_down("left"))
                {
                    owner()->get<StateMachine>("states")->axis = 2;
                    owner()->get<StateMachine>("states")->does<PlayerWalk>();
                }
                if(Game::instance().is_down("right"))
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