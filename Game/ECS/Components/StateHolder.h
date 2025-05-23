#pragma once

#include "../../../RetroCS/RetroCS.h"

#include "../Utils/State.h"

namespace YoKard
{
    namespace ECS
    {
        struct StateHolder : public Component
        {
            BaseState* entry_point;
            BaseState* state;

            bool initialized;
                
            StateHolder() : Component()
            {
                entry_point = nullptr;
                state = nullptr;
                initialized = false;
                scene->system("statemachine")->upload(this);
            }

            template <typename T>
            void go_to()
            {
                if(state != nullptr) state->exit();
                state = new T();
                state->holder = this; 
                state->enter();
            }

            void go_to_entry_point()
            {
                if(!initialized && entry_point != nullptr)
                {
                    if(state != nullptr) state->exit();
                    state = entry_point;
                    state->holder = this; 
                    state->enter();
                    entry_point = nullptr;
                    initialized = true;
                }
            }
        };
    }
}