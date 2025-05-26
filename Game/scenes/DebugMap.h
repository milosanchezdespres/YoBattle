#pragma once

#include "../../retrocs/retrocs.h"

namespace game
{
    namespace ecs
    {
        struct DebugMap: Scene
        {
            DebugMap() : Scene() {}

            void OnEnter() override
            {
                spawn<Entity>({7, 2});
                spawn<Entity>({4, 8});
                spawn<Entity>({1, 1});

                remove_at(4, 8);
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}