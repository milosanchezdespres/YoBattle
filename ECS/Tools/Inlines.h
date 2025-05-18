#pragma once

#include <string>
#include <iostream>
using namespace std;

inline void print(string str) { cout << str << endl; cout << endl; }
inline void print(int i) { print(to_string(i)); }
inline void print(float f) { print(to_string(f)); }
