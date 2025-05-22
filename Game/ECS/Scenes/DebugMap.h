#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Entity2D.h"

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

                add<Entity2D>("debug");

                get<Entity2D>("debug")->get<Image>()->texture = "player";

                get<Entity2D>("debug")->get<Image>()->scale = 5;
                get<Entity2D>("debug")->get<Image>()->rotation = 45;

                get<Entity2D>("debug")->get<Image>()->x = 100;
                get<Entity2D>("debug")->get<Image>()->y = 100;
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}