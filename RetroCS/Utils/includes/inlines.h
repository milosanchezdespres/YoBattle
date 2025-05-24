#pragma once

#include "ext_includes.h"

namespace retrocs
{
    namespace utils
    {
        inline void print(string obj) { cout << "< " + obj << endl << endl; }
        inline void print(float obj) { cout << "< " + to_string(obj) << endl << endl; }
        inline void print(int obj) { cout << "< " + to_string(obj) << endl << endl; }

        inline string type_to_string(type_index type)
        {
            int status = 0;
            char* demangled = abi::__cxa_demangle(type.name(), nullptr, nullptr, &status);
            string result = (status == 0) ? demangled : type.name();
            free(demangled);

            size_t pos = result.rfind("::");
            if (pos != string::npos)
                result = result.substr(pos + 2);

            while (!result.empty() && result.back() == '*')
                result.pop_back();

            while (!result.empty() && isspace(result.back()))
                result.pop_back();

            transform(result.begin(), result.end(), result.begin(), ::tolower);

            return result;
        }

        inline string type_to_string(const auto& obj) { return type_to_string(std::type_index(typeid(obj))); } 

        template <typename T>
        inline string type_to_string() { return type_to_string(type_index(typeid(T))); } 
    }
}

namespace std
{
    std::vector<std::string> split(const std::string& str, char delim)
    {
        std::stringstream ss(str);
        std::string item;
        std::vector<std::string> tokens;
        while (std::getline(ss, item, delim)) { tokens.push_back(item); }
        return tokens;
    }
}