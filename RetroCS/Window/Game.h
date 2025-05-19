#pragma once

#include "../Tools/Externals.h"

#include "GameLogic.h"

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

                template <typename T>
                void start(string _title)
                {
                    game_logic = new T();

                    title = _title;

                    InitWindow(width, height, title.c_str());
                    SetWindowState(FLAG_FULLSCREEN_MODE);

                    SetTargetFPS(60);
                    HideCursor();

                    width = GetMonitorWidth(0);
                    height = GetMonitorHeight(0);

                    game_logic->enter();
                }

                void update()
                {
                    while (!WindowShouldClose())
                    {
                        if (IsKeyPressed(KEY_ESCAPE)) { delete this; }
                        if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

                        game_logic->events();

                        game_logic->update(GetFrameTime());

                        BeginDrawing();
                        ClearBackground(game_logic->background_color);

                        game_logic->draw();

                        EndDrawing();
                    }
                }

            private:
                GameLogic* game_logic = nullptr;

                Game() = default;
                ~Game() = default;
        };
    };
}