#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Entities/Character.h"

#include "../data/states/NPCIdle.h"
//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct NPC : public Character
        {
            NPC () : Character()
            {
                get<Sprite>("body")->texture_alias = "player";
                //default sprite

                //...
                get<StateMachine>("states")->does<NPCIdle>();
            }
        };
    }
}
