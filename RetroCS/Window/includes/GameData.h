#pragma once

#include "../../Tools/Tools.h"

namespace RetroCS
{
    namespace Window
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

        struct texture : public Resource<Texture2D>
        {
            texture() : Resource<Texture2D>() { }

            texture(string _name, string _folders = "") { load(_name, _folders); }
                        
            void load(string _name, string _folders = "") override
            {
                const char* path = __get_path("png", _name, _folders);

                data = new Texture2D(LoadTexture(path));
                name = _name;
            }


            void unload() override
            {
                if (data != nullptr)
                {
                    UnloadTexture(*data);
                    data = nullptr;
                }
            }

            ~texture() override
            {
                if (data != nullptr)
                {
                    UnloadTexture(*data);
                    delete data;
                    data = nullptr;
                }
            }
        };

        //...

        struct GameData
        {
            string title = "untitled";

            int width = 600;
            int height = 600;

            vector<BaseResource*> resources;
            unordered_map<string, int> resources_by_names;

            template <typename T, typename = enable_if_t<is_base_of_v<BaseResource, T>>>
            void load(string _name, string _folders = "") {
                if (resources_by_names.find(_name) != resources_by_names.end()) {
                    std::cout << "Resource already loaded: " << _name << std::endl;
                    return;
                }

                T* res = new T();
                res->id = static_cast<int>(resources.size());
                res->load(_name, _folders);

                resources.push_back(res);
                resources_by_names[_name] = res->id;
            }

            template <typename T, typename = enable_if_t<is_base_of_v<BaseResource, T>>>
            T* get(const string& _name)
            {
                auto it = resources_by_names.find(_name);
                if (it == resources_by_names.end()) {
                    std::cout << "Resource not found: " << _name << std::endl;
                    return nullptr;
                }

                int index = it->second;
                if (index < 0 || index >= resources.size()) {
                    std::cout << "Invalid resource index: " << index << std::endl;
                    return nullptr;
                }

                return static_cast<T*>(resources[index]);
            }

            GameData(string _title, int _width, int _height)
            {
                title = _title;
                width = _width;
                height = _height;
            }

            GameData() {}
            ~GameData()
            {
                for (auto* resource : resources)
                {
                    resource->unload();
                    delete resource;
                }
                resources.clear();
            }
        };
    }
}