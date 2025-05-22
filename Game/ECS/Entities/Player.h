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

            void OnInit() override
            {
                Character::OnInit();
                
                get<Image>()->texture = "player";

                //...
            }
        };
    }
}