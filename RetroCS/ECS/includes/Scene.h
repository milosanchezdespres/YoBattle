#pragma once

#include "Entity.h"
#include "System.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene : public Container<Entity>
        {
            vector<BaseSystem*> systems;

            Scene() : Container<Entity>() {}

            template <typename T, typename = enable_if_t<is_base_of_v<BaseSystem, T>>>
            void attach()
            {
                systems.push_back(new T());
                systems[systems.size() - 1]->resume();
            }

            void enter() { OnEnter(); }
            void update() { for(auto* system : systems) { if (system) system->update(); } }
            void render() { for(auto* entity : *this) { if (entity) entity->render(); } }
            void exit() { OnExit(); }

            virtual void OnEnter() {}
            virtual void OnExit() {}

            void clear() override
            {
                Container::clear();

                systems.clear();
            }
        };
    }
}