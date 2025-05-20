#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/Controller.h"

#include "../data/states/PlayerIdle.h"
#include "../data/states/PlayerWalk.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct ControllerSystem : public System<Controller>
        {
            ControllerSystem () : System<Controller>() { }
 
            void OnDraw(Entity* owner, Controller* component) override
            {
                if(component->alias == "camera")
                {
                    if(Game::instance().is_down("up")) { Game::instance().camera()->move_up(Game::instance().delta()); }
                    else if(Game::instance().is_down("down")) { Game::instance().camera()->move_down(Game::instance().delta()); }
                    else if(Game::instance().is_down("left")) { Game::instance().camera()->move_left(Game::instance().delta()); }
                    else if(Game::instance().is_down("right")) { Game::instance().camera()->move_right(Game::instance().delta()); }
                }
                else if(component->alias == "move")
                {
                    if(Game::instance().is_down("up"))
                    {
                        owner->get<StateMachine>("states")->axis = 0;
                        owner->get<StateMachine>("states")->does<PlayerWalk>();
                    }
                    else if(Game::instance().is_down("down"))
                    {
                        owner->get<StateMachine>("states")->axis = 1;
                        owner->get<StateMachine>("states")->does<PlayerWalk>();
                    }
                    else if(Game::instance().is_down("left"))
                    {
                        owner->get<StateMachine>("states")->axis = 2;
                        owner->get<StateMachine>("states")->does<PlayerWalk>();
                    }
                    else if(Game::instance().is_down("right"))
                    {
                        owner->get<StateMachine>("states")->axis = 3;
                        owner->get<StateMachine>("states")->does<PlayerWalk>();
                    }
                    else { owner->get<StateMachine>("states")->does<PlayerIdle>(); }
                }
            }
        };
    }
}