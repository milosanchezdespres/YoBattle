#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Entities/Entity2D.h"

#include "../Systems/ControllerSystem.h"
#include "../Systems/StateMachineSystem.h"
#include "../Systems/AnimationSystem.h"

#include "../Components/Controller.h"
#include "../Components/StateMachine.h"
#include "../Components/Animations.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Character : public Entity2D
        {
            Character () : Entity2D()
            {
                add<Controller>("ui");
                upload_to<ControllerSystem, Controller>(Game::instance().scene(), "ui");

                add<StateMachine>("states");
                upload_to<StateMachineSystem, StateMachine>(Game::instance().scene(), "states");

                get<StateMachine>("states")->axis = 1;
                get<StateMachine>("states")->move_speed = 45;

                add<Animations>("anim");
                upload_to<AnimationSystem, Animations>(Game::instance().scene(), "anim");

                get<Animations>("anim")->add_animation("idle", 0);
                get<Animations>("anim")->add_frame(4, "idle", 0);

                get<Animations>("anim")->add_animation("idle", 1);
                get<Animations>("anim")->add_frame(1, "idle", 1);

                get<Animations>("anim")->add_animation("idle", 2);
                get<Animations>("anim")->add_frame(7, "idle", 2);

                get<Animations>("anim")->add_animation("idle", 3);
                get<Animations>("anim")->add_frame(10, "idle", 3);

                get<Animations>("anim")->add_animation("walk", 0);
                get<Animations>("anim")->add_frame(3, "walk", 0);
                get<Animations>("anim")->add_frame(4, "walk", 0);
                get<Animations>("anim")->add_frame(5, "walk", 0);

                get<Animations>("anim")->add_animation("walk", 1);
                get<Animations>("anim")->add_frame(0, "walk", 1);
                get<Animations>("anim")->add_frame(1, "walk", 1);
                get<Animations>("anim")->add_frame(2, "walk", 1);

                get<Animations>("anim")->add_animation("walk", 2);
                get<Animations>("anim")->add_frame(6, "walk", 2);
                get<Animations>("anim")->add_frame(7, "walk", 2);
                get<Animations>("anim")->add_frame(8, "walk", 2);

                get<Animations>("anim")->add_animation("walk", 3);
                get<Animations>("anim")->add_frame(9, "walk", 3);
                get<Animations>("anim")->add_frame(10, "walk", 3);
                get<Animations>("anim")->add_frame(11, "walk", 3);

                //...
            }
        };
    }
}
