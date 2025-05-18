#pragma once

#include "BaseObject/BaseObject.h"
#include "BaseObject/Container.h"
using namespace BaseECS;

#include "Component.h"

namespace ECS
{
    struct Entity : public Container
    {
        Entity() : Container() {}

        template <typename T>
        void attach(string _alias) { add<T>(_alias); }
        
        Component* component(string _alias) { return get<Component>(_alias); }

        template <typename T>
        T* component(string _alias) { return get<T*>(_alias); }
    };
}