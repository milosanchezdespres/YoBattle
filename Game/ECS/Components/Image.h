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

            Image() : Component() {}
        };
    }
}