#pragma once

#include "Externals.h"

inline void debug(string value) { cout << "<< " + value  + " <<" << endl; }

inline void debug(int value) { cout << "<< " + to_string(value)  + " <<" << endl; }
