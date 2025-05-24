#pragma once

#include "../../Utils/Utils.h"

namespace retrocs
{
    namespace window
    {
        bool ___window_initialized = false;

        class GameWindow
        {
        public:
            GameWindow(BaseGameData* data, std::string title, int width = 0, int height = 0)
            {
                if (___window_initialized) { throw std::runtime_error("GameWindow already initialized"); }
                ___window_initialized = true;

                data->title = title;

                if(width == 0 || height == 0)
                {
                    width = GetMonitorWidth(0);
                    height = GetMonitorHeight(0);

                    InitWindow(width, height, title.c_str());
                    SetWindowState(FLAG_FULLSCREEN_MODE);
                }
                else
                {
                    InitWindow(width, height, title.c_str());
                }

                SetTargetFPS(60);
                HideCursor();

                width = GetMonitorWidth(0);
                height = GetMonitorHeight(0);

                data->width = width;
                data->height = height;
            }

            void update(BaseGameData* data, GameLogic* logic)
            {
                while (!WindowShouldClose())
                {
                    if (IsKeyPressed(KEY_ESCAPE)) { delete this; }
                    if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

                    data->delta = GetFrameTime();

                    logic->update();

                    logic->draw(data->background_color);
                }
            }

            ~GameWindow() {}
        };
    }
}
