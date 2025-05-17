#include "RenderSystem.h"
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
        if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

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

void RaylibHandler::load_texture(string _alias)
{
    if (textureByAlias.find(_alias) == textureByAlias.end())
    {
        string path = "assets/" + _alias + ".png";

        textures.push_back(LoadTexture(path.c_str()));
        textureByAlias[_alias] = textures.size() - 1;
    }
}

void RaylibHandler::unload_texture(string _alias)
{
    auto it = textureByAlias.find(_alias);

    if (it != textureByAlias.end())
    {
        size_t index = it->second;

        UnloadTexture(textures[index]);

        textures.erase(textures.begin() + index);
        textureByAlias.erase(it);

        for (auto& [key, idx] : textureByAlias) {  if (idx > index) {  --idx; } }
    }
}

bool RaylibHandler::is_texture_loaded(string _alias)
    { return textureByAlias.find(_alias) != textureByAlias.end(); }

Texture2D& RaylibHandler::texture(string alias)
    { return textures[textureByAlias.at(alias)]; }

void RaylibHandler::blit(Sprite* sprite)
{
    if (sprite->visible)
    {
        __position = { (float)((int)(sprite->x)), (float)((int)(sprite->y)) };

        if (sprite->size == 0)
            { DrawTextureEx(texture(sprite->texture), __position, sprite->rotation, sprite->scale, WHITE); }
        else
        {
            __sourceRec = { (float)(sprite->h_tile_index * sprite->size), (float)(sprite->v_tile_index * sprite->size), (float)(sprite->scale * sprite->size), (float)(sprite->scale * sprite->size)};
            DrawTextureRec(texture(sprite->texture), __sourceRec, __position, WHITE);
        }
    }
}
