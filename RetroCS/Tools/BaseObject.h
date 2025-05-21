#pragma once

#include "Externals.h"

namespace RetroCS
{
    namespace Tools
    {
        struct BaseObject
        {
            string __str;

            int ID;
            string alias;
            BaseObject* __parent;

            json __json_buffer;

            BaseObject() { init(); }
            virtual ~BaseObject() {} 

            void init(int _ID = -1, string _alias = "", BaseObject* parent = nullptr)
            {
                ID = _ID;
                alias = _alias;
                __parent = parent;
            }

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

            BaseObject* owner() { return __parent; }

            template <typename T>
            T* owner() { return dynamic_cast<T*>(__parent); }
        };
    }
}