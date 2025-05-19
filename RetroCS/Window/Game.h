#pragma once

#include "../Tools/Externals.h"

namespace RetroCS
{
    namespace GameWindow
    {
        class Game 
        {
            public:
                Game(const Game&) = delete;
                Game& operator=(const Game&) = delete;

                string title;
                int width, height;

                static Game& instance()
                {
                    static Game __instance;
                    return __instance;
                }

                void start(string _title)
                {
                    title = _title;

                    InitWindow(width, height, title.c_str());
                    SetWindowState(FLAG_FULLSCREEN_MODE);

                    SetTargetFPS(60);
                    HideCursor();

                    width = GetMonitorWidth(0);
                    height = GetMonitorHeight(0);
                }

                void update()
                {
                    while (!WindowShouldClose())
                    {
                        if (IsKeyPressed(KEY_ESCAPE)) { delete this; }
                        if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

                        BeginDrawing();
                        ClearBackground(BLACK);

                        EndDrawing();
                    }
                }

            private:
                Game() = default;
                ~Game() = default;
        };
    };
}