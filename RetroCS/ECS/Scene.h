#pragma once

#include "../Tools/Container.h"
using namespace RetroCS::Tools;

#include "Entity.h"

namespace RetroCS
{
    namespace ECS
    {
        struct Scene : Container<Entity>
        {
            Scene() : Container() {}
        };
    }
}