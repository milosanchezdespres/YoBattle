#pragma once

#include "../../../RetroCS/RetroCS.h"

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
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}