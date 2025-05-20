#pragma once

#include "../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Sprite : public Component
        {
            string texture_alias;

            float x, y;

            Sprite () : Component()
            {
                texture_alias = "";

                x = 0;
                y = 0;
            }
        };
    }
}