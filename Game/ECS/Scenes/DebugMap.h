#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Player.h"

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

                add<Player>();

                //HUB::set<Player*>(get<Player>());
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}