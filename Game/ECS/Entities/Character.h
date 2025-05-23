#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/AnimEntity2D.h"

#include "../Components/StateHolder.h"

namespace YoKard
{
    namespace ECS
    {
        struct DefaultState : public BaseState
        {
            DefaultState() : BaseState() {}

            string OnName() override { return "default"; }
        };

        struct Character : public AnimEntity2D
        {
            Character() : AnimEntity2D() {}

            void OnInit() override
            {
                AnimEntity2D::OnInit();

                add<StateHolder>();
                get<StateHolder>()->entry_point = new DefaultState();

                //...

                InitializeEntryPoint();
            }

            virtual void tp(int i, int j)
            {
                //...
            }

            virtual void InitializeEntryPoint() {}
        };
    }
}