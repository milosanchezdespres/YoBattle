#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../components/Sprite.h"

namespace yokard
{
    namespace ecs
    {
        struct Entity2D : public Entity
        {
            Entity2D() : Entity() { }

            void _on_init() override
            {
                add<Sprite>();
                main_drawable_name = "sprite";

                //...
            }

            //void _on_destroy() override {}
        };
    }
}
