#pragma once

#include "../Tools/BaseObject.h"

#include "nlohman_json.h"
using json = nlohmann::json;

namespace RetroCS
{
    namespace DATA
    {
        template <typename T, typename = enable_if_t<is_base_of<BaseObject, T>::value>>
        inline void save_to(T* base_object, string path)
        {
            json _json = base_object->to_json();

            //...
        }

        template <typename T, typename = enable_if_t<is_base_of<BaseObject, T>::value>>
        inline void load_from(T* base_object, string path)
        {
            json _json = {};

            //...

            base_object->from_json(_json);
        }
    }
}