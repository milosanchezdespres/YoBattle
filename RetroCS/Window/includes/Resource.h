#pragma once

#include "../../Utils/Utils.h"

namespace retrocs
{
    namespace window
    {
        struct BaseResource
        {
            int id = -1;
            string name = "no_name";
            char path_buffer[512];

            BaseResource() {}
            virtual ~BaseResource() = default;

            virtual void load(string _name, string _folders = "") {}
            virtual void unload() {}

            const char* __get_path(const string& ext, const string& _name, const string& _folders = "")
            {
                string folder = _folders.empty() ? "" : _folders + "/";
                string full_path = "Game/assets/" + folder + _name + "." + ext;

                strncpy(path_buffer, full_path.c_str(), sizeof(path_buffer) - 1);
                
                path_buffer[sizeof(path_buffer) - 1] = '\0';
                return path_buffer;
            }
        };

        template <typename T>
        struct Resource : public BaseResource
        {
            T* data = nullptr;

            Resource() : BaseResource(), data(nullptr) {}
            ~Resource() {}
        };
    }
}