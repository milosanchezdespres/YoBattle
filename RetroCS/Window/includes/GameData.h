#pragma once

#include "../../Utils/Utils.h"
#include "../../ECS/ECS.h"

namespace retrocs
{
    namespace window
    {
        bool ___window__data_initialized;

        struct BaseGameData
        {
            vector<BaseResource*> resources;
            unordered_map<string, int> resources_by_names;

            string title;

            int width;
            int height;

            Color background_color;
            float delta;

            Scene* entry_point;

            BaseGameData() { }

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
                    std::cout << "Resource not found: <" << _name << ">" << std::endl;
                    return nullptr;
                }

                int index = it->second;
                if (index < 0 || index >= resources.size()) {
                    std::cout << "Invalid resource index: <" << index << ">" << std::endl;
                    return nullptr;
                }

                return static_cast<T*>(resources[index]);
            }

            ~BaseGameData() {}
        };

        template <typename T, typename = enable_if_t<is_base_of_v<Scene, T>>>
        struct GameData : public BaseGameData
        {
            GameData() : BaseGameData()
            {
                if (___window__data_initialized) { throw std::runtime_error("GameData already initialized"); }
                else { ___window__data_initialized = true; }

                background_color = BLACK;

                entry_point = new T();
            }

            ~GameData() { delete entry_point; }
        };
    }
}