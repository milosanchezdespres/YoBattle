#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/AnimEntity2D.h"
#include "../Components/StateHolder.h"

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

                add<StateHolder>();

                //...
            }

            virtual void tp(int i, int j)
            {
                //...
            }
        };
    }
}