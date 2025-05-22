#pragma once

#include "Entity.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene : public Container<Entity>
        {
            Scene() : Container<Entity>() {}

            void enter() { OnEnter(); }
            void exit() { OnExit(); }

            virtual void OnEnter() {}
            virtual void OnExit() {}
        };
    }
}