#pragma once
//...

#include "BaseObject/BaseObject.h"
#include "Entity.h"

using namespace BaseECS;
using namespace ECS;

#include <iostream>
using namespace std;

namespace ECS
{
    inline void print(string str) { cout << str << endl; cout << endl; }
    inline void print(int i) { print(to_string(i)); }
    inline void print(float f) { print(to_string(f)); }
}