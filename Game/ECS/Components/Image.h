#pragma once

#include "../../../RetroCS/RetroCS.h"

namespace YoKard
{
    namespace ECS
    {
        struct Image : public Component
        {
            float x, y, rotation, scale;

            string texture;

            bool in_bound;

            Image() : Component()
            {
                x = 0;
                y = 0;
                rotation = 0;
                scale = 1;

                in_bound = false;
            }
        };
    }
}