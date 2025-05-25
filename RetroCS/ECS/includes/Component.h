#pragma once

#include "drawable.h"

namespace retrocs
{
    namespace ecs
    {
        struct Component : public drawable
        {
            Component() : drawable() { }

            bool is_in_bound() { return ___screen_data->in_bound; }
        };
    }
}