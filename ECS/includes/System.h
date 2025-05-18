#pragma once

#include "../Tools/BaseObject.h"
#include "../Tools/Container.h"

#include "Component.h"

namespace ECS
{
    struct BaseSystem : public BaseObject
    {
        BaseSystem() : BaseObject() {}

        virtual void update(float delta) {}

        virtual void OnUpdate(float delta, Component* _component) {}

        virtual bool __is_valid(Component* component) { return component != nullptr; }
    };

    template <typename M, typename = enable_if_t<is_base_of_v<Component, M>>>
    struct System : public Container<Component>, public BaseSystem
    {
        System() : Container<Component>(), BaseSystem() {}

        void update(float delta) override
        { for(auto* component : all()) { { if(__is_valid(component)) { OnUpdate(delta, component); } } } }

        void upload(Component* component) { this->add(component); }

        M* cast(Component* component) { return dynamic_cast<M*>(component); }
    };
}