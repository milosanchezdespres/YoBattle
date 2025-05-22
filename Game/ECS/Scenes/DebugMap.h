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