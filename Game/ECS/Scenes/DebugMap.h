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

                debug(game()->get<texture>("player")->data->width);

                //...
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}