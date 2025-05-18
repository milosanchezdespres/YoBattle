#pragma once

#include "Entity.h"

namespace ECS
{
    struct Scene : public Container
    {
        Scene() : Container() {}

        ~Scene() { Exit(); }

        void Enter() { OnEnter(); }

        void Update() { OnUpdate(); }

        void Exit()
        {
            for(Entity* obj : all<Entity>()) { obj->clear(); }
            clear();
        }

        Entity* entity(string _alias) { return get<Entity>(_alias); }

        template <typename T>
        T* entity(string _alias) { return get<T*>(_alias); }

        template <typename T, typename = std::enable_if_t<is_base_of_v<Component, T>>>
        void attach(string entity_alias, string component_alias) { entity(entity_alias)->attach<T>(component_alias); }

        /*template <typename T, typename = std::enable_if_t<std::is_base_of_v<BaseSystem, T>>>
        void start()
        {
            //...
        }*/
    
        virtual void OnEnter() {}
        virtual void OnUpdate() {}
        virtual void OnExit() {}
    };
}