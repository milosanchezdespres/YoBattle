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
                add<Controller>("ui");
                upload_to<ControllerSystem, Controller>(Game::instance().scene(), "ui");
                
                get<StateMachine>("states")->does<PlayerIdle>();
            }
        };
    }
}
