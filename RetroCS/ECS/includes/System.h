#pragma once

#include "Component.h"

namespace RetroCS
{
    namespace ECS
    {
        struct BaseSystem
        {
            bool __on;

            BaseSystem() {}

            void resume() { __on = true; }
            void pause() { __on = false; }

            virtual void upload(Component* component) {}
            virtual void update() {}
        };
        
        template <typename T, typename = enable_if_t<is_base_of_v<Component, T>>>
        struct System : public BaseSystem
        {
            vector<T*> registered_components;

            void upload(Component* component) override { registered_components.push_back(dynamic_cast<T*>(component)); }

            void update() override { if(__on) for(T* component : registered_components) { OnUpdate(component); } }

            virtual void OnUpdate(T* component) {}
        };
    }
}