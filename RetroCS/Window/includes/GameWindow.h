#pragma once

#include "../../Tools/Tools.h"
#include "../../Data/includes/Hub.h"
#include "GameData.h"
#include "Camera.h"

namespace RetroCS
{
    namespace Window
    {
        class GameWindow
        {
            public:
                Color background_color;

                GameData* data = nullptr;
                SceneManager* scene_manager;

                GameWindow(const GameWindow&) = delete;
                GameWindow& operator=(const GameWindow&) = delete;

                float __stored_delta;

                static GameWindow& instance()
                {
                    static GameWindow __instance;
                    return __instance;
                }

                template <typename T, typename = enable_if_t<is_base_of_v<Scene, T>>>
                void start(string _title, int _width = 0, int _height = 0)
                {
                    background_color = BLACK;
                    __stored_delta = 0;

                    data = new GameData(_title, _width, _height);

                    if(_width == 0 || _height == 0)
                    {
                        data->width = GetMonitorWidth(0);
                        data->height = GetMonitorHeight(0);

                        InitWindow(data->width, data->height, _title.c_str());
                        SetWindowState(FLAG_FULLSCREEN_MODE);
                    }
                    else { InitWindow(_width, _height, _title.c_str()); }

                    SetTargetFPS(60);
                    HideCursor();

                    _width = GetMonitorWidth(0);
                    _height = GetMonitorHeight(0);

                    scene_manager = new SceneManager();
                    scene_manager->go_to(new T());

                    Camera::instance().init(data->width, data->height);
                }

                void update()
                {
                    while (!WindowShouldClose())
                    {
                        if (IsKeyPressed(KEY_ESCAPE)) { delete this; }
                        if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

                        __stored_delta = GetFrameTime();

                        scene_manager->update();

                        BeginDrawing();
                        ClearBackground(background_color);

                        scene_manager->render();

                        EndDrawing();
                    }
                }

            private:
                GameWindow() = default;
                ~GameWindow()
                {
                    HUB::clear();

                    delete scene_manager;
                    
                    delete data;
                    data = nullptr;
                }
        };

        inline GameWindow& window() { return GameWindow::instance(); }

        inline GameData* game() { return GameWindow::instance().data; }

        inline float delta() { return GameWindow::instance().__stored_delta; }
    }
}