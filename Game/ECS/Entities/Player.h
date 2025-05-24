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

                add_animation("test2");
                add_frame("test2", 8, 0.5f);
                add_frame("test2", 9, 0.5f);
                add_frame("test2", 10, 0.5f);
                add_frame("test2", 1, 0.5f);
                add_frame("test2", 4, 0.5f);
                //...
            }

            void InitializeEntryPoint() override;
        };

        struct PlayerWalk;
        //...
        
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

                holder->go_to<PlayerWalk>();
            }

            void OnExit() override
            {
                //...
            }
        };

        struct PlayerWalk : public State<Player>
        {
            PlayerWalk() : State<Player>() {}

            string OnName() override { return "walk"; }

            void OnEnter() override
            {
                //...

                owner()->play("test2");
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