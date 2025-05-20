#pragma once

#include "Component.h"
#include "Entity.h"

namespace RetroCS
{
    namespace ECS
    {
        template <typename T>
        struct EntityComponentPair
        {
            T* data;
            Entity* owner;
        };

        struct BaseSystem
        {
            BaseSystem() {}

            virtual void events();
            virtual void update(float delta);
            virtual void draw();
        };

        template <typename T>
        struct System : public BaseSystem
        {
            vector<EntityComponentPair<T>> components;

            System() : BaseSystem () {}

            void upload(EntityComponentPair<T> pair) { components.push_back(pair); }

            void events() override { for (auto& component : components) { OnEvents(component.owner, dynamic_cast<T*>(component.data)); } }

            void update(float delta) override { for (auto& component : components) { OnUpdate(delta, component.owner, dynamic_cast<T*>(component.data)); } }

            void draw() override { for (auto& component : components) { OnDraw(component.owner, dynamic_cast<T*>(component.data)); } }

            virtual void OnEvents(Entity* owner, T* component) {}
            virtual void OnUpdate(float delta, Entity* owner, T* component) {}
            virtual void OnDraw(Entity* owner, T* component) {}
        };
    }
}