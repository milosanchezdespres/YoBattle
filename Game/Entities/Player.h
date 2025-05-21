#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Entities/Character.h"
//...

#include "../Components/RobotTeam.h"
//...

#include "../data/states/PlayerIdle.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Player : public Character
        {
            Player () : Character()
            {
                get<Sprite>("body")->texture_alias = "player";

                add<RobotTeam>("team1");
                //...
                
                get<StateMachine>("states")->does<PlayerIdle>();
            }
        };
    }
}
