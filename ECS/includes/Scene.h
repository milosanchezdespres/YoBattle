#pragma once

#include "Entity.h"

namespace ECS
{
    struct Scene : Container<Entity>
    {
        Scene() : Container() {}

        void Enter() { OnEnter(); }

        void Update(float delta) { OnUpdate(delta); }

        void Exit()
        {
            clear();
            OnExit();
        }

        virtual void OnEnter() {}
        virtual void OnUpdate(float delta) {}
        virtual void OnExit() {}
    };
}