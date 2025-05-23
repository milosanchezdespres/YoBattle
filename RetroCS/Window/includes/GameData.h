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
        };

        struct input
        {
            string name;

            KeyboardKey key;
            GamepadButton gamepad;

            bool was_down;
            bool currently_down;
        };

        struct button : public Resource<input>
        {
            button() : Resource<input>() {}

            void load(string _name, string _folders = "") override
            {
                data = new input();

                data->name = _name;

                auto parts = split(_folders, ';');
                if (parts.size() != 2)
                {
                    data->key = KEY_NULL;
                    data->gamepad = GAMEPAD_BUTTON_UNKNOWN;
                    return;
                }

                if (raylib_key_map.count(parts[0])) data->key = raylib_key_map[parts[0]];
                else data->key = KEY_NULL;

                if (raylib_gamepad_map.count(parts[1])) data->gamepad = raylib_gamepad_map[parts[1]];
                else data->gamepad = GAMEPAD_BUTTON_UNKNOWN;
            }

            bool is_down()
            {
                if (data->gamepad != GAMEPAD_BUTTON_UNKNOWN && IsGamepadAvailable(0))
                {
                    if (IsGamepadButtonDown(0, data->gamepad))
                        return true;
                }

                return IsKeyDown(data->key);
            }

            bool is_pressed()
            {
                if (data->gamepad != GAMEPAD_BUTTON_UNKNOWN && IsGamepadAvailable(0)) { data->currently_down = IsGamepadButtonDown(0, data->gamepad); }

                if (!data->currently_down) { data->currently_down = IsKeyDown(data->key); }

                bool just_pressed = data->currently_down && !data->was_down;
                data->was_down = data->currently_down;

                return just_pressed;
            }

            void unload() override
            {
                delete data;
                data = nullptr;
            }
        };

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