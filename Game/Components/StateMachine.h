#pragma once

#include "../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct StateMachine;

        struct State
        {
            string name;

            Entity* _owner;
            StateMachine* __parent;

            State(string _name, Entity* __owner) { name =_name; _owner = __owner; }

            void enter() { OnEnter(); }
            void update(float delta) { OnUpdate(delta); }
            void exit() { OnExit(); }

            template <typename T>
            void does() { __parent->template does<T>(); }

            Entity* owner() { return _owner; }
            StateMachine* parent() { return __parent; }

            template <typename T>
            T* owner() { return dynamic_cast<T*>(_owner); }

            virtual void OnEnter() {}
            virtual void OnUpdate(float delta) {}
            virtual void OnExit() {}
        };

        struct StateMachine : public Component
        {
            State* state;

            int axis;
            float move_speed;

            StateMachine () : Component()
            {
                state = nullptr;
                axis = -1;
                move_speed = 0;
            }

            template <typename T>
            void does()
            {
                if(state != nullptr) { state->exit(); state = nullptr; }
                state = new T(owner<Entity>());
                state->__parent = this;
                state->enter();
            }

            string current() { return state->name; }

            void update(float delta) { state->update(delta); }

            bool is_valid() { return state != nullptr; }
        };
    }
}
