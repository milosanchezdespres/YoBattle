#pragma once

#include "../../../RetroCS/RetroCS.h"

namespace YoKard
{
    namespace ECS
    {
        struct StateHolder;

        struct BaseState
        {
            StateHolder* holder;

            BaseState() { holder = nullptr; }
            ~BaseState() { delete holder; holder = nullptr; }

            string name() { return OnName(); }

            void enter() { OnEnter(); }
            void update() { OnUpdate(); }
            void exit() { OnExit(); }

            virtual string OnName() { return "no_state"; }
            virtual void OnEnter() {}
            virtual void OnUpdate() {}
            virtual void OnExit() {}
        };

        template <typename T, typename = enable_if_t<is_base_of_v<Entity, T>>>
        struct State : public BaseState
        {
            State() : BaseState() {}

            T* owner() { return holder->template owner<T>(); }
        };
    }
}