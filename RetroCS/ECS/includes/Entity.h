#pragma once

#include "Component.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Entity : public Container<Component>
        {
            Entity() : Container<Component>() {}

            virtual void render() {}
        };
    }
}