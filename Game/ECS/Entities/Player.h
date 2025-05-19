#pragma once

#include "../Entities/Character.h"
#include "../Components/Controller.h"

namespace YOBATTLE
{
    struct Player : public Character
    {
        Player() : Character() { }

        void OnInit() override
        {
            Character::OnInit();

            add<Controller>("main");
            //...

            //...
        }
    };
}