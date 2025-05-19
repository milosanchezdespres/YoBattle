#pragma once

#include "../Entities/Entity2D.h"
#include "../Components/State.h"
#include "../Components/Animator.h"

namespace YOBATTLE
{
    struct Character : public Entity2D
    {
        Character() : Entity2D() { }

        void OnInit() override
        {
            Entity2D::OnInit();

            add<State>("info");
            add<Animator>("anim");
            //...

            //...
        }
    };
}