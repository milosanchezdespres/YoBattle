#pragma once

#include <string>
#include <iostream>
using namespace std;

namespace BaseECS
{
    struct BaseObject
    {
        string __str;

        int ID;
        string alias;
        BaseObject* parent;

        BaseObject() { init(); }
        virtual ~BaseObject() {} 

        void init(int _ID = -1, string _alias = "", BaseObject* parent = nullptr)
        {
            ID = _ID;
            alias = _alias;
            parent = parent;
        }
    };
}