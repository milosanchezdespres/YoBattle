#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Components/Animator.h"

namespace YoKard
{
    namespace ECS
    {
        //TO DO : HANDLE LOOP/NO LOOP

        struct AnimationSystem : public System<Animator>
        {
            void OnUpdate(Animator* component) override
            {
                if(component->is_playing())
                {
                    component->current()->timer += delta();

                    if(component->current()->timer >= component->duration())
                    {
                        component->increase_current_frame_index();

                        component->current()->timer = 0;

                        if(component->has_frame_index_maxed_out()) component->reset_current_animation();
                    }

                    component->set_frame();
                }
            }
        };
    }
}