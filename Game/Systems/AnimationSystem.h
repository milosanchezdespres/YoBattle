#pragma once

#include "../../RetroCS/RetroCS.h"
#include "../Components/Animations.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct AnimationSystem : public System<Animations>
        {
            Animation* previous_animation;
            Animation* animation;

            AnimationSystem () : System<Animations>() { previous_animation = nullptr; animation = nullptr; }

            void OnDraw(Entity* owner, Animations* component) override
            {
                previous_animation = animation;
                animation = component->animation(owner->get<StateMachine>("states")->current(), owner->get<StateMachine>("states")->axis);

                if(animation != nullptr)
                {
                    if(previous_animation != animation && previous_animation != nullptr)
                    {
                        previous_animation->timer = 0;
                        previous_animation->index = 0;
                        animation->timer = 0;
                        animation->index = 0;
                    }

                    animation->timer += Game::instance().delta();
                    float frame_time = component->speed / 60;

                    if(animation->timer >= frame_time)
                    {
                        animation->timer = 0;
                        animation->index++;

                        if(animation->index >= animation->frames.size()) { animation->index = 0; }
                    }

                    if(animation->index < animation->frames.size())
                    { owner->get<Sprite>("body")->tile->index = animation->frames[animation->index]; }
                }
            }
        };
    }
}