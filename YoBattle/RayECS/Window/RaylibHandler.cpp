#include "RenderSystem.h"
#include "RaylibHandler.h"

RaylibHandler::RaylibHandler(string title) : SceneManager()
{
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);

    InitWindow(screenWidth, screenHeight, title.c_str());
    SetWindowState(FLAG_FULLSCREEN_MODE);

    SetTargetFPS(60);

    background = Color(WHITE);
    __position = new Vector2();
    __sourceRec = new Rectangle();
}

void RaylibHandler::Update()
{
    OnInit();

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE)) { delete this; }
        if (IsKeyPressed(KEY_F11)) { ToggleFullscreen(); }

        OnEvent();

        BeginDrawing();
        ClearBackground(background);

        OnUpdate(GetFrameTime());

        OnDraw();

        EndDrawing();
    }
}

int RaylibHandler::screen_width() { return GetScreenWidth(); }

int RaylibHandler::screen_height() { return GetScreenHeight(); }

RaylibHandler::~RaylibHandler()
{
    delete __position;
    delete __sourceRec;
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
        __position->x = (int)(sprite->x);
        __position->y = (int)(sprite->y);

        if (sprite->size == 0)
            { DrawTextureEx(texture(sprite->texture), *__position, sprite->rotation, sprite->scale, WHITE); }
        else
        {
            __sourceRec->x = (float)(sprite->h_tile_index * sprite->size);
            __sourceRec->y = (float)(sprite->v_tile_index * sprite->size);
            __sourceRec->width = (float)(sprite->scale * sprite->size);
            __sourceRec->height = (float)(sprite->scale * sprite->size);

            DrawTextureRec(texture(sprite->texture), *__sourceRec, *__position, WHITE);
        }
    }
}

void RaylibHandler::write(string text, int font_size, float x, float y, Color color)
    { DrawText(text.c_str(), x, y, font_size, color); }
