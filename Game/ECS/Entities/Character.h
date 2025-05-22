#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Entity2D.h"

namespace YoKard
{
    namespace ECS
    {
        struct Character : public Entity2D
        {
            Character() : Entity2D() {}

            void init() override
            {
                Entity2D::init();

                //...
            }

            virtual void tp(int i, int j)
            {
                //...
            }
        };
    }
}