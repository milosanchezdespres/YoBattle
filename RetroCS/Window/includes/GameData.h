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
            string title;

            int width;
            int height;

            Color background_color;
            float delta;

            Scene* entry_point;

            BaseGameData() {}
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