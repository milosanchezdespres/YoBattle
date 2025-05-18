#pragma once

#include "../Tools/BaseObject.h"
#include "../Tools/Container.h"

#include "Component.h"

namespace ECS
{
    struct Entity : Container<Component>
    {
        Entity() : Container() {}
    };
}