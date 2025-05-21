#pragma once

#include "../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Image : public Component
        {
            string texture_alias;

            float x, y, r;
            float scale_h, scale_v;

            Image () : Component()
            {
                texture_alias = "";

                x = 0;
                y = 0;
                r = 0;

                scale_h = 1;
                scale_v = 1;
            }
        };
    }
}
