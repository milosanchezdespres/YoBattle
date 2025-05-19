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

                    logic->update(GetFrameTime());

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

        bool is_texture_loaded(string _alias)
            { return textureByAlias.find(_alias) != textureByAlias.end(); }

        Texture2D& texture(string alias)
            { return textures[textureByAlias.at(alias)]; }

                template <typename T>
                void go_to() { logic->go_to<T>(); }

        private:
            GameLogic* logic = nullptr;

            string title;
            int width, height;

            vector<Texture2D> textures;
            unordered_map<string, int> textureByAlias;

            Game() = default;
            ~Game() = default;
    };
}