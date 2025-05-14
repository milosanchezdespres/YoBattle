#include "GameLoop.h"

GameLoop::GameLoop(string title)
{
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);

    InitWindow(screenWidth, screenHeight, "Display Image");
    //InitWindow(600, 600, title.c_str());
    //SetWindowState(FLAG_FULLSCREEN_MODE);
}

GameLoop::~GameLoop()
{
    OnClose();
    CloseWindow();
}

void GameLoop::Update()
{
    if (!_initialized)
    {
        OnInit();
        _initialized = true;
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) { delete this; }

        if (IsKeyPressed(KEY_F11)) {
            if (IsWindowState(FLAG_FULLSCREEN_MODE)) {
                ClearWindowState(FLAG_FULLSCREEN_MODE);
            }
            else {
                SetWindowState(FLAG_FULLSCREEN_MODE);
            }

            OnEvent();
        }

        OnUpdate();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        OnDraw();

        EndDrawing();
    }
}

void GameLoop::load_texture(string name, string path)
{
    if (path == "") { path = name; }
    _textures[name] = LoadTexture(("assets/" + path + ".png").c_str());
}

void GameLoop::unload_texture(string name)
{
    UnloadTexture(_textures[name]);
    _textures.erase(name);
}

const Texture2D& GameLoop::texture(string name) { return _textures[name]; }

void GameLoop::blit(Sprite* sprite)
{
    __source__buffer = { 0, 0, (float) (sprite->size), (float)(sprite->size) };
    __dest__buffer = { sprite->x, sprite->y, __source__buffer.width * sprite->scale, __source__buffer.height * sprite->scale };
    DrawTexturePro(texture(sprite->texture), __source__buffer, __dest__buffer, {0, 0}, 0.0f, WHITE);
}
