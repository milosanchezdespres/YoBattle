#pragma once

#include "Window/Window.h"
#include "Utils/Utils.h"
#include "ECS/ECS.h"
//...

namespace retrocs
{
    namespace hub
    {
        inline BaseGameData* data;
        inline GameLogic* screen;
        inline GameWindow* window;

        template <typename T, typename = enable_if_t<is_base_of_v<Scene, T>>>
        inline void init(string title, int width = 0, int height = 0)
        {
            data = new GameData<T>();
            screen = new GameLogic();
            window = new GameWindow(data, title, width, height);
            
            screen->init(data->entry_point);

            //...
        }

        inline void update() { window->update(data, screen); }

        inline Scene* scene() { return screen->scene; }

        //...
    }
}

using namespace retrocs;