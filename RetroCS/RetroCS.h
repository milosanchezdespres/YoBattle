#pragma once

#include "Window/Window.h"
#include "Utils/Utils.h"
#include "ECS/ECS.h"
//...

namespace retrocs
{
    namespace hub
    {
        inline SimpleCamera* camera;
        inline BaseGameData* data;
        inline GameLogic* screen;
        inline GameWindow* window;

        template <typename T, typename = enable_if_t<is_base_of_v<Scene, T>>>
        inline void init(string title, int width = 0, int height = 0)
        {
            camera = new SimpleCamera();
            data = new GameData<T>();
            screen = new GameLogic();
            window = new GameWindow(data, title, width, height);
            
            screen->init(data->entry_point);
            camera->init(data->width, data->height);

            //...
        }

        inline void update()
        {
            window->update(camera, data, screen);

            delete window;
            delete data;
            delete screen;
            delete camera;
        }

        inline Scene* scene() { return screen->scene; }

        inline bool is_down(string key) { return data->get<retrocs::window::button>(key)->is_down(); }
        inline bool is_pressed(string key) { return data->get<retrocs::window::button>(key)->is_pressed(); }

        //...
    }
}

using namespace retrocs;