#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Entities/Entity2D.h"
#include "../Components/Animator.h"

namespace YoKard
{
    namespace ECS
    {
        struct AnimEntity2D : public Entity2D
        {
            AnimEntity2D() : Entity2D() {}

            void OnInit() override
            {
                Entity2D::OnInit();

                add<Animator>();
            }

            void add_animation(string animation_name, string _texture = "")
            {
                if(_texture == "") _texture = get<Image>()->texture;
                get<Animator>()->add_animation(animation_name, _texture);
            }

            void add_frame(string animation_name, int index, float duration) { get<Animator>()->add_frame(animation_name, index, duration); }

            void resume() { get<Animator>()->resume(); }
            void pause() { get<Animator>()->pause(); }
            bool is_playing() { return get<Animator>()->is_playing(); }
            bool is_paused() { return get<Animator>()->is_paused(); }

            void play(string animation_name) { get<Animator>()->play(animation_name, get<Image>(), get<Sprite>()); }
        };
    }
}