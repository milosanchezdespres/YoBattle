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

                add_animation("test", "player");
                add_frame("test", 2, 0.5f);
                add_frame("test", 3, 0.5f);
                add_frame("test", 6, 0.5f);
                //...
                
                play("test");
            }

            virtual void tp(int i, int j)
            {
                //...
            }
        };
    }
}