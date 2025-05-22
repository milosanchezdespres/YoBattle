#pragma once

#include "../../Tools/Tools.h"

namespace RetroCS
{
    namespace HUB
    {
        inline vector<any> ___values;
        inline unordered_map<string, int> ___values_per_alias;

        template <typename T>
        inline void init(string alias, T value)
        {
            ___values.push_back(value);
            ___values_per_alias[alias] = ___values.size() - 1;
        }

        inline void set(string alias, any value) { ___values[___values_per_alias[alias]] = value; }

        template <typename T>
        inline T get(string alias) { return any_cast<T>(___values[___values_per_alias[alias]]) ; }

        inline void clear()
        {
            ___values.clear();
            ___values_per_alias.clear();
        }
    }
}