#pragma once

#include "Component.h"

namespace retrocs
{
    namespace ecs
    {
        struct Entity : public box<Component>
        {
            Entity() : box<Component>() { }
        };
    }
}