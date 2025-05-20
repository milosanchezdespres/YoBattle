#pragma once

#include "../Tools/Container.h"
using namespace RetroCS::Tools;

#include "Entity.h"
#include "System.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene : public Container<Entity>
        {
            vector<BaseSystem*> systems;
            unordered_map<type_index, int> system_by_type;

            template <typename T>
            void add_component(string entity_alias, string component_alias) { get(entity_alias)->template add<T>(component_alias); }

            template <typename T, typename M>
            M* component(string entity_alias, string component_alias) { return get<T>(entity_alias)->template get<M>(component_alias); }

            template <typename T>
            void attach()
            {
                systems.push_back(new T());
                system_by_type[type_index(typeid(T))] = systems.size() - 1;
            }

            template <typename T, typename M>
            void upload_to(Entity* entity, string component_alias)
            {
                M* component = entity->template get<M>(component_alias);
                auto* _pair = new EntityComponentPair<M>(entity, component);

                BaseSystem* base_system = systems[system_by_type[type_index(typeid(T))]];
                System<M>* system = dynamic_cast<System<M>*>(base_system);

                system->upload(*_pair);
            }

            Scene() : Container() {}

            virtual void enter() {}
            virtual void events() { for(auto* sys : systems) { sys->events(); } }
            virtual void update(float delta) { for(auto* sys : systems) { sys->update(delta); } }
            virtual void draw() { for(auto* sys : systems) { sys->draw(); } }
            virtual void exit() {}
        };
    }
}