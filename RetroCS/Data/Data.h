#pragma once

#include "nlohman_json.h"
using json = nlohmann::json;

namespace RetroCS
{
    namespace DATA
    {
        struct DataObject
        {
            json __json_buffer;

            json to_json()
            {
                __json_buffer = {};

                OnJsonWrite();

                return __json_buffer;
            }

            void from_json(json _data)
            {
                __json_buffer = _data;

                OnJsonRead();
            }

            virtual void OnJsonWrite() {}
            virtual void OnJsonRead() {}
        };

        template <typename T, typename = enable_if_t<is_base_of<DataObject, T>::value>>
        inline void save_to(T* data_object, string path)
        {
            json _json = data_object->to_json();

            //...
        }

        template <typename T, typename = enable_if_t<is_base_of<DataObject, T>::value>>
        inline void load_from(T* data_object, string path)
        {
            json _json = {};

            //...

            data_object->from_json(_json);
        }
    }
}