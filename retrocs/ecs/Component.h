#pragma once

#include "View.h"

namespace retrocs
{
    namespace ecs
    {
        struct Component : public View
        {
            Component(int _id) : View(_id) {}
        };
    }
}