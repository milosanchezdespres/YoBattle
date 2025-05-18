#pragma once

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

inline void print(string str) { cout << str << endl; cout << endl; }
inline void print(int i) { print(to_string(i)); }
inline void print(float f) { print(to_string(f)); }

std::string to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return s;
}