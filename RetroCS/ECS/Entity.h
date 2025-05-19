#pragma once

#include "../Tools/Container.h"
using namespace RetroCS::Tools;

#include "Component.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Entity : public Container<Component>
        {
            Entity() : Container() {}
        };
    }
}