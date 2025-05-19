#pragma once

#include "../../../ECS/ECS.h"
#include "../Components/Sprite.h"
#include "../Components/State.h"

namespace YOBATTLE
{
    struct Entity2D : public Entity
    {
        Entity2D() : Entity() { }

        void OnInit() override
        {
            add<Sprite>("body");

            //...
        }
    };
}