#pragma once

#include "ext_includes.h"

namespace retrocs
{
    namespace utils
    {
        struct object
        {
            int id;
            string alias;

            object* __parent;

            bool __initialized;

            object() { __initialized = false; }

            void init(int _id = -1, string _alias = "", object* _parent = nullptr)
            {
                if(!__initialized)
                {
                    id = _id;
                    alias = _alias;

                    if(alias == "") alias = type_to_string(*this);

                    __parent = _parent;

                    _on_init();

                    __initialized = true;
                }
            }

            object* owner() { return __parent; }

            template <typename T>
            T* owner() { return dynamic_cast<T*>(__parent); }

            ~object()
            {
                id = -1;
                alias = "";

                delete __parent;

                __initialized = false;

                _on_destroy();
            }

            virtual void _on_init() {}
            virtual void _on_destroy() {}
        };
    }
}