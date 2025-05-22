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

            void OnInit() override
            {
                AnimEntity2D::OnInit();

                //...
            }

            virtual void tp(int i, int j)
            {
                //...
            }
        };
    }
}