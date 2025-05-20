#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Entities/Entity2D.h"

#include "../Systems/ControllerSystem.h"
#include "../Systems/StateMachineSystem.h"

#include "../Components/Controller.h"
#include "../Components/StateMachine.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Character : public Entity2D
        {
            Character () : Entity2D()
            {
                add<Controller>("move");
                upload_to<ControllerSystem, Controller>(Game::instance().scene(), "move");

                add<StateMachine>("states");
                upload_to<StateMachineSystem, StateMachine>(Game::instance().scene(), "states");

                //...
            }
        };
    }
}
