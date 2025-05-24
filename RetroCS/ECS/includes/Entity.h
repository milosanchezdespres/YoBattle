#pragma once

#include "Component.h"

namespace retrocs
{
    namespace ecs
    {
        struct Entity : box<Component>
        {
            Entity() : box<Component>() { }

            ~Entity() { }
        };
    }
}