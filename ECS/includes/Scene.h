#pragma once

#include "Entity.h"
#include "System.h"

namespace ECS
{
    struct Scene : Container<Entity>
    {
        Container<BaseSystem>* __systems;

        Scene() : Container() { __systems = new Container<BaseSystem>(); }

        template <typename T>
        void attach() { __systems->add<T>(to_lower(type_index(typeid(T)).name())); }

        template <typename T>
        T* sys() { return __systems->get<T>(to_lower(type_index(typeid(T)).name())); }

        vector<BaseSystem*> all_systems() { return __systems->all(); }

        void Enter() { OnEnter(); }

        void Exit()
        {
            for(auto* entity : all())
            {
                entity->clear();
                delete entity;
            }

            for(auto* system : all_systems()) { delete system; }

            clear();

            OnExit();
        }

        virtual void OnEnter() {}
        virtual void OnExit() {}
    };
}