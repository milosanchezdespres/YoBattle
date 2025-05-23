#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Player.h"

#include "../Systems/AnimationSystem.h"
#include "../Systems/StateMachine.h"

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

                display_fps = true;
                display_draw_count = true;

                fps_display_x = 40;
                fps_display_y = 40;
                fps_display_size = 40;

                game()->load<texture>("player");
                //...

                attach<AnimationSystem>();
                attach<StateMachine>();
                //...

                add<Player>();
                get<Player>()->get<Image>()->x = 50;
                get<Player>()->get<Image>()->y = 50;

                camera().set_zoom(8);
                camera().follow(get<Player>()->get<Image>()->x, get<Player>()->get<Image>()->y);
            }

            void OnExit() override { }
        };
    }
}