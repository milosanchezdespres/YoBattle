#pragma once

#include "../../../ECS/ECS.h"
#include "../../../MAP/Camera.h"
using namespace U8INT_MAP;

#include "../Components/State.h"
#include "../Components/Sprite.h"
#include "../Components/Animator.h"

#include "../Entities/Character.h"

namespace YOBATTLE
{
    struct AnimationSystem : System<State>
    {
        float frame_time;
        int start_frame_offset;
        int max_frame;
        int current_frame;

        AnimationSystem() : System()
        {
            frame_time = 0;
            start_frame_offset = 0;
            max_frame = 1;
            current_frame = 0;

            //...
        }

        void OnUpdate(float delta, Component* _component) override
        {
            State* state = cast(_component);
            Sprite* sprite = dynamic_cast<Entity2D*>(state->parent)->get<Sprite>("body");
            Animator* animator = dynamic_cast<Character*>(state->parent)->get<Animator>("anim");

            sprite->tile_index = state->direction;

            if(state->action == "idle")
            {
                max_frame = 1;
                start_frame_offset = 1;
                current_frame = 0; 
            }
            else if(state->action == "walk")
            {
                max_frame = 3;
                start_frame_offset = 0;
            }

            animator->time += delta;
            frame_time = animator->speed / 100;
            
            if(animator->time >= frame_time)
            {
                animator->time = 0;
                current_frame++;

                if(current_frame >= max_frame) { current_frame = 0; }
            }

            sprite->tile_index = start_frame_offset + state->direction + current_frame;
        }
    };
}