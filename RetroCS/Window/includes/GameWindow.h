#pragma once

#include "../../Tools/Tools.h"
#include "../../Data/includes/Hub.h"
#include "GameData.h"
#include "Camera.h"

namespace RetroCS
{
    namespace Window
    {
        inline bool display_draw_count = false;
        inline int draw_count = 0;

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
                        _width = GetMonitorWidth(0);
                        _height = GetMonitorHeight(0);

                        InitWindow(_width, _height, _title.c_str());
                        SetWindowState(FLAG_FULLSCREEN_MODE);
                    }
                    else { InitWindow(_width, _height, _title.c_str()); }

                    data = new GameData(_title, _width, _height); 

                    SetTargetFPS(60);
                    HideCursor();

                    _width = GetMonitorWidth(0);
                    _height = GetMonitorHeight(0);

                    scene_manager = new SceneManager();
                    scene_manager->go_to(new T());

                    std::init_reverse_keys();

                    data->load<button>("up", "KEY_W; GAMEPAD_BUTTON_LEFT_FACE_UP");
                    data->load<button>("left", "KEY_A; GAMEPAD_BUTTON_LEFT_FACE_LEFT");
                    data->load<button>("right", "KEY_D; GAMEPAD_BUTTON_LEFT_FACE_RIGHT");
                    data->load<button>("down", "KEY_S; GAMEPAD_BUTTON_LEFT_FACE_DOWN");

                    Camera::instance().init(_width, _height);
                }

                void update()
                {
                    while (!WindowShouldClose())
                    {
                        if (IsKeyPressed(KEY_ESCAPE)) { delete this; }
                        if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

                        __stored_delta = GetFrameTime();

                        scene_manager->update(data);

                        BeginDrawing();
                        ClearBackground(background_color);

                        scene_manager->render();

                        if(display_draw_count)
                        {
                            DrawText(TextFormat("Sprites Drawn: %d", draw_count), 10, 10, 20, RED);

                            draw_count = 0;
                        }

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