#pragma once

#include "ext_includes.h"
#include "object.h"

namespace retrocs
{
    namespace utils
    {
        template <typename T, typename = enable_if_t<is_base_of_v<object, T>>>
        struct box : public object
        {
            box() : object() {}

            void _on_init() override
            {
                //..
            }

            void _on_destroy() override
            {
                //..
            }
        };
    }
}