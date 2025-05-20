#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Entities/Character.h"

#include "../data/states/PlayerIdle.h"
//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct Player : public Character
        {
            Player () : Character()
            {
                //...
                get<StateMachine>("states")->does<PlayerIdle>();
            }
        };
    }
}
