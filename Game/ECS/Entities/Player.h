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

                add_animation("test");
                add_frame("test", 2, 0.5f);
                add_frame("test", 3, 0.5f);
                add_frame("test", 6, 0.5f);
                //...
            }

            void InitializeEntryPoint() override;
        };

        struct PlayerIdle : public State<Player>
        {
            PlayerIdle() : State<Player>() {}

            string OnName() override { return "idle"; }

            void OnEnter() override
            {
                //...

                owner()->play("test");
            }

            void OnUpdate() override
            {               
                //...
            }

            void OnExit() override
            {
                //...
            }
        };

        void Player::InitializeEntryPoint() { get<StateHolder>()->entry_point = new PlayerIdle(); }
    }
}