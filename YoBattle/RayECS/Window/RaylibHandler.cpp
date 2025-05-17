#include "RaylibHandler.h"

RaylibHandler::RaylibHandler(string title)
{
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);

    InitWindow(screenWidth, screenHeight, title.c_str());
    //SetWindowState(FLAG_FULLSCREEN_MODE);

    SetTargetFPS(60);
}

void RaylibHandler::Update()
{
    OnInit();

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE)) { delete this; }

        if (IsKeyPressed(KEY_F11))
        {
            if (IsWindowState(FLAG_FULLSCREEN_MODE)) { ClearWindowState(FLAG_FULLSCREEN_MODE); }
            else { SetWindowState(FLAG_FULLSCREEN_MODE); }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        OnUpdate(GetFrameTime());

        OnDraw();

        EndDrawing();
    }
}

RaylibHandler::~RaylibHandler()
{
    //...
}
