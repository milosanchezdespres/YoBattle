#pragma once

#include "Entity.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene : public Container<Entity>
        {
            Scene() : Container<Entity>() {}
        };
    }
}