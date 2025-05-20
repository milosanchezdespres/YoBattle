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

                void load_texture(string _alias, string _folders = "")
                {
                    if (textureByAlias.find(_alias) == textureByAlias.end())
                    {
                        if (_folders != "") { _folders += "/"; }
                        string path = "Game/assets/" + _folders + _alias + ".png";

                        textures.push_back(LoadTexture(path.c_str()));
                        textureByAlias[_alias] = textures.size() - 1;
                    }
                }

                void unload_texture(string _alias)
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

                bool is_texture_loaded(string _alias) { return textureByAlias.find(_alias) != textureByAlias.end(); }

                Texture2D& texture(string alias) { return textures[textureByAlias.at(alias)]; }

            private:
                vector<Texture2D> textures;
                unordered_map<string, int> textureByAlias;

                GameLogic* game_logic = nullptr;

                Game() = default;
                ~Game() { game_logic->exit(); };
        };
    };
}