#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/AnimEntity2D.h"

namespace YoKard
{
    namespace ECS
    {
        struct Character : public AnimEntity2D
        {
            Character() : AnimEntity2D() {}

            void init() override
            {
                AnimEntity2D::init();

                //...
            }

            virtual void tp(int i, int j)
            {
                //...
            }
        };
    }
}