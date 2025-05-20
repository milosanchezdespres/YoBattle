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
            string name;

            Character* owner;
            StateMachine* __parent;

            State(string _name, Character* _owner) { name =_name; owner = _owner; }

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
                axis = -1;
            }

            template <typename T>
            void does()
            {
                if(state != nullptr) { state->exit(); state = nullptr; }
                state = new T(owner<Character>());
                state->__parent = this;
                state->enter();
            }

            string current() { return state->name; }

            void update(float delta)
            {
                if(state != nullptr)
                { state->update(delta); }
            }
        };
    }
}
