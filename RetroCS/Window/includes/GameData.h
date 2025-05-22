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

            BaseResource() {}

            virtual void load(string _name, string _folders = "") {}
            virtual void unload() {}

            const char* __get_path(string ext, string _name, string _folders = "")
            {
                if (_folders != "") { _folders += "/"; }
                return ("Game/assets/" + _folders + _name + "." + ext).c_str();
            }
        };

        template <typename T>
        struct Resource : public BaseResource
        {
            T* data = nullptr;

            Resource() : BaseResource() {}
        };

        struct texture : public Resource<Texture2D>
        {
            texture() : Resource<Texture2D>() { }

            texture(string _name, string _folders = "") { load(_name, _folders); }

            void load(string _name, string _folders = "") override
            {
                data = new Texture(LoadTexture(__get_path("png", _name, _folders)));
                name = _name;
            }

            void unload() override { UnloadTexture(*data); }
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
            void load(string _name, string _folders = "")
            {
                auto it = resources_by_names.find(_name);

                if (it != resources_by_names.end())
                {
                    resources.push_back(new T());
                    resources_by_names[_name] = resources.size() - 1;
                    resources[resources.size() - 1]->id = resources.size() - 1;
                    resources[resources.size() - 1]->load(_name, _folders);
                }
            }

            template <typename T, typename = enable_if_t<is_base_of_v<BaseResource, T>>>
            T* get(string _name) { return resources[resources_by_names[_name]]; }

            GameData(string _title, int _width, int _height)
            {
                title = _title;
                width = _width;
                height = _height;
            }

            GameData() {}
            ~GameData() { for(auto* resource : resources) { resource->unload(); } }
        };
    }
}