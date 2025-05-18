#pragma once

#include "Entity.h"

namespace ECS
{
    struct Scene : public Container
    {
        Scene() : Container() {}

        Entity* entity(string _alias) { return get<Entity>(_alias); }

        template <typename T>
        T* entity(string _alias) { return get<T*>(_alias); }

        template <typename T>
        void attach(string entity_alias, string component_alias) { entity(entity_alias)->attach<T>(component_alias); }
    };
}