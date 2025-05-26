#pragma once

#include "../utils.h"

#include "BaseScene.h"

namespace retrocs
{
    namespace ecs
    {
        struct Scene : public BaseScene
        {
            Scene() : BaseScene() {}

            void enter() { OnEnter(); }

            void update()
            {
                //...
            }

            void exit() { OnExit(); }

            virtual void OnEnter() {}
            virtual void OnExit() {}
        };
    }
}