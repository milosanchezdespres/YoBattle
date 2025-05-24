#pragma once

#include "drawable.h"

namespace retrocs
{
    namespace ecs
    {
        struct Component : drawable
        {
            Component() : drawable() { }

            ~Component() { }
        };
    }
}