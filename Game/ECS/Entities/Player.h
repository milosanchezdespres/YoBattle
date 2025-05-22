#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Character.h"

namespace YoKard
{
    namespace ECS
    {
        struct Player : public Character
        {
            Player() : Character() {}

            void init() override
            {
                Character::init();
                
                get<Image>()->texture = "player";

                //...
            }
        };
    }
}