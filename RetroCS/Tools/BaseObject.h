#pragma once

#include "includes.h"

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

            BaseObject() { init(); }
            virtual ~BaseObject() {} 

            void init(int _ID = -1, string _alias = "", BaseObject* parent = nullptr)
            {
                ID = _ID;
                alias = _alias;
                __parent = parent;
            }

            BaseObject* owner() { return __parent; }

            template <typename T>
            T* owner() { return dynamic_cast<T*>(__parent); }
        };
    }
}