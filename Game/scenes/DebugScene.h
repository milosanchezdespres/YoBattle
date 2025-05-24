#pragma once

#include "../../RetroCS/RetroCS.h"

namespace yokard
{
    namespace ecs
    {
        struct DebugScene : Scene
        {
            DebugScene() : Scene() { }

            void _on_init() override
            {
                hub::data->background_color = BLUE;

                //...
            }

            void _on_enter() override
            {
                //...
            }

            void _on_exit() override
            {
                //...
            }

            void _on_destroy() override
            {
                //...
            }

            Scene* clone() const override { return new DebugScene(*this); }
        };
    }
}

//because this scene is entry_point :
using namespace yokard;
using namespace yokard::ecs;