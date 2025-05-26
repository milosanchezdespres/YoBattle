#pragma once

#include "../utils.h"

#include "BaseScene.h"
#include "Entity.h"

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
                for (int id : in_bounds())
                {
                    Entity entity = get<Entity>(id);
                    
                    entity.update(screen_space);
                }
            }

            void exit() { OnExit(); }

            virtual void OnEnter() {}
            virtual void OnExit() {}
        };
    }
}