#pragma once

#include "../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Character;
        struct StateMachine;

        struct State
        {
            Character* owner;
            StateMachine* __parent;

            State(Character* _owner) { owner = _owner; }

            void enter() { OnEnter(); }
            void update(float delta) { OnUpdate(delta); }
            void exit() { OnExit(); }

            template <typename T>
            void does() { __parent->template does<T>(); }

            virtual void OnEnter() {}
            virtual void OnUpdate(float delta) {}
            virtual void OnExit() {}
        };

        struct StateMachine : public Component
        {
            State* state;

            int axis;

            StateMachine () : Component()
            {
                state = nullptr;
                axis = 1;
            }

            template <typename T>
            void does()
            {
                if(state != nullptr) { state->exit(); state = nullptr; }
                state = new T(owner<Character>());
                state->__parent = this;
                state->enter();
            }

            string is_doing() { return to_lower(type_index(typeid(this)).name()); }

            void update(float delta)
            {
                if(state != nullptr)
                { state->update(delta); }
            }
        };
    }
}
