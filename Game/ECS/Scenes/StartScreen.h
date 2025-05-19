#pragma once

#include "../../../ECS/ECS.h"
#include "../../../MAP/MAP.h"
using namespace U8INT_MAP;

#include "../Systems/SpriteRenderSystem.h"
#include "../Entities/Entity2D.h"

namespace YOBATTLE
{
    struct StartScreen : public Scene
    {
        bool map_refresh;
        metatile test_map[2500] = {0};
        RenderTexture2D test_map_surface;

        U8INT_MAP::Camera* camera;

        StartScreen() : Scene() {}

        void OnEnter() override
        {
            Game::instance().load_texture("tileset");
            Game::instance().load_texture("player");

            camera = new U8INT_MAP::Camera();
            camera->zoom = 5;

            attach<SpriteRenderSystem>();
            sys<SpriteRenderSystem>()->camera = camera;

            add<Entity2D>("player");
            get("player")->get<Sprite>("body")->texture = "player";
            get("player")->get<Sprite>("body")->position.x = 130;
            get("player")->get<Sprite>("body")->position.y = 130;
            get("player")->get<Sprite>("body")->tile_index = 1;
            get("player")->get<Sprite>("body")->tile_size = 16;

            sys<SpriteRenderSystem>()->upload(get("player")->get<Sprite>("body"));

            vector<metatile> new_map = map_make(50, 50);
            for (int i = 0; i < 100; ++i) { test_map[i] = new_map[i]; }
            map_refresh = true;
        }
 
        void OnDraw() override
        {
            //...

            if (map_refresh)
            {
                test_map_surface = map_draw("tileset", test_map, 8, 50, 50);
                map_refresh = false;
            }

            //for test purposes, later, store a buffer for rect, position
            DrawTexturePro(test_map_surface.texture, {0, 0, (float)test_map_surface.texture.width, -(float)test_map_surface.texture.height}, {0, 0, (float)test_map_surface.texture.width * camera->zoom, (float)test_map_surface.texture.height * camera->zoom}, {0, 0}, 0.0f, WHITE);
        
            sys<SpriteRenderSystem>()->update(0);
        }

        void OnExit() override
        {
            Game::instance().unload_texture("tileset");
            Game::instance().unload_texture("player");

            //...
        }
    };
}