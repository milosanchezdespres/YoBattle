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
            unordered_map<string, int> systems_by_name;

            Scene() : Container<Entity>() {}

            template <typename T, typename = enable_if_t<is_base_of_v<BaseSystem, T>>>
            void attach()
            {
                string name = Alias::to_string(type_index(typeid(T)));

                auto it = systems_by_name.find(name);
                if (it == systems_by_name.end())
                {
                    systems.push_back(new T());
                    systems.back()->resume();
                    systems_by_name[name] = systems.size() - 1;

                }

            }

            BaseSystem* system(const string& name)
            {
                auto it = systems_by_name.find(name);

                if (it != systems_by_name.end() && it->second < systems.size())
                { return systems[it->second]; } else { return nullptr; }
            }

            void enter() { OnEnter(); }
            void update() { for(auto* system : systems) { if (system) system->update(); } }
            void render() { for(auto* entity : *this) { if (entity) entity->render(); } }
            void exit() { OnExit(); }

            void OnAdd(string name) override { get(name)->init(); }

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