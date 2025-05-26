#pragma once

#include "VirtualScreen.h"

namespace retrocs
{
    namespace ecs
    {
        struct Scene : public VirtualScreen
        {
            Scene() : VirtualScreen() {}

            //...
        };
    }
}