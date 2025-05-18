#pragma once

#include "GameLogic.h"

#include <string>
using namespace std;

namespace RAYWIN
{
    class Game 
    {
        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            static Game& instance()
            {
                static Game __instance;
                return __instance;
            }

            void start(GameLogic* _logic, string _title)
            {
                logic = _logic; 

                title = _title;
                width = GetMonitorWidth(0);
                height = GetMonitorHeight(0);

                InitWindow(width, height, title.c_str());
                SetWindowState(FLAG_FULLSCREEN_MODE);

                SetTargetFPS(60);
            }

            void update()
            {
                logic->start();

                while (!WindowShouldClose())
                {
                    if (IsKeyPressed(KEY_ESCAPE)) { delete this; }
                    if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

                    BeginDrawing();
                    ClearBackground(logic->background);

                    logic->update();

                    EndDrawing();
                }
            }

        private:
            GameLogic* logic = nullptr;

            string title;
            int width, height;

            Game() = default;
            ~Game() = default;
    };
}