#pragma once

#include "View.h"

namespace retrocs
{
    namespace ecs
    {
        struct Entity : public View
        {
            Entity(int _id) : View(_id) {}
        };
    }
}