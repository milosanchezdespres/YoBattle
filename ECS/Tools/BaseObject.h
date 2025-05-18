#pragma once

#include <string>
#include <iostream>
using namespace std;

struct BaseObject
{
    string __str;

    int ID;
    string alias;
    BaseObject* parent;

    BaseObject() { init(); }
    virtual ~BaseObject() {} 

    void init(int _ID = -1, string _alias = "", BaseObject* _parent = nullptr)
    {
        ID = _ID;
        alias = _alias;
        parent = _parent;

        OnInit();
    }

    virtual void OnInit() {}
};