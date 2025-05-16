#pragma once

#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "Scene.h"
#include "../Game/CustomEntityFactory.h"

namespace ECS
{
    class Game {
        private:
            bool _debug_mode;

        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            EntityFactory* factory;

            static Game& loop()
            {
                static Game instance;
                return instance;
            }

            void Init(EntityFactory* custom_factory, bool debug_mode = false)
            {
                _debug_mode = debug_mode;

                if (!_debug_mode)
                {
                    int screenWidth = GetMonitorWidth(0);
                    int screenHeight = GetMonitorHeight(0);

                    InitWindow(screenWidth, screenHeight, "Display Image");
                    //SetWindowState(FLAG_FULLSCREEN_MODE);

                    SetTargetFPS(60);
                }

                factory = custom_factory;
            }

            void Update()
            {
                if (_debug_mode)
                {
                    Scene* test = new Scene("test");

                    test->load(factory);

                    cout << test << endl;
                }

                while (!_debug_mode && !WindowShouldClose())
                {
                    if (IsKeyPressed(KEY_ESCAPE)) { delete this; }

                    if (IsKeyPressed(KEY_F11))
                    {
                        if (IsWindowState(FLAG_FULLSCREEN_MODE)) { ClearWindowState(FLAG_FULLSCREEN_MODE); }
                        else { SetWindowState(FLAG_FULLSCREEN_MODE); }
                    }

                    BeginDrawing();
                    ClearBackground(RAYWHITE);

                    //...

                    EndDrawing();
                }
            }

        private:
            Game() {}
    };
}

#endif