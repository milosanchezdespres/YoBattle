#pragma once

#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace std
{
    inline string debug(string value) { cout << "  <<" + value  + " >>  " << endl << endl; return value; }
    inline string debug(float value) { return debug(to_string(value)); }
    inline string debug(int value) { return debug(to_string(value)); }
    inline string debug(int value1, int value2) { return debug(to_string(value1) + ", " + to_string(value2)); }
    inline string debug(float value1, float value2) { return debug(to_string(value1) + ", " + to_string(value2)); }

    inline size_t hash_coordinates(int cell_x, int cell_y) { return ((size_t)cell_x * 73856093) ^ ((size_t)cell_y * 19349663); }
    //...
    
}

using namespace std;
