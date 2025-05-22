#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Entity2D.h"
#include "../Components/Animator.h"

namespace YoKard
{
    namespace ECS
    {
        struct AnimEntity2D : public Entity2D
        {
            AnimEntity2D() : Entity2D() {}

            void init() override
            {
                Entity2D::init();

                add<Animator>();
            }
        };
    }
}