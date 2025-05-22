#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Player.h"
#include "../Systems/AnimationSystem.h"

namespace YoKard
{
    namespace ECS
    {
        struct DebugMap : public Scene
        {
            DebugMap() : Scene() { }

            void OnEnter() override
            {
                window().background_color = BLUE;

                game()->load<texture>("player");
                //...

                attach<AnimationSystem>();
                //...

                add<Player>();
                get<Player>()->get<Image>()->scale = 10;
                get<Player>()->get<Image>()->x = 450;
                get<Player>()->get<Image>()->y = 150;
            }

            void OnExit() override { }
        };
    }
}