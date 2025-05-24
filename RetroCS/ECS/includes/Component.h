#pragma once

#include "drawable.h"

namespace retrocs
{
    namespace ecs
    {
        struct Component : public drawable
        {
            Component() : drawable() { }
        };
    }
}