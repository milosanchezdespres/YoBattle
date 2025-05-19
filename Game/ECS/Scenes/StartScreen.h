#pragma once

#include "../../../ECS/ECS.h"
#include "../../../MAP/MAP.h"
using namespace U8INT_MAP;

#include "../Systems/SpriteRenderSystem.h"
#include "../Entities/Character.h"

namespace YOBATTLE
{
    struct StartScreen : public Scene
    {
        bool map_refresh;

        metatile test_map[2500] = {0};
        Rectangle map_source;
        Rectangle map_dest;
        Vector2 map_origin;

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

            add<Character>("player");
            get("player")->get<Sprite>("body")->texture = "player";
            get("player")->get<Sprite>("body")->position.x = 130;
            get("player")->get<Sprite>("body")->position.y = 130;
            get("player")->get<Sprite>("body")->tile_index = 1;
            get("player")->get<Sprite>("body")->tile_size = 16;

            sys<SpriteRenderSystem>()->upload(get("player")->get<Sprite>("body"));

            vector<metatile> new_map = map_make(50, 50);
            for (int i = 0; i < 100; ++i) { test_map[i] = new_map[i]; }
            map_refresh = true;

            map_source = {0, 0, 0, 0};
            map_dest = {0, 0, 0, 0};
            map_origin = {0, 0};
        }
 
        void OnDraw() override
        {
            //...

            if (map_refresh)
            {
                test_map_surface = map_draw("tileset", test_map, 8, 50, 50);
                map_refresh = false;
            }

            map_source.x = 0;
            map_source.y = 0;
            map_source.width = (float) test_map_surface.texture.width;
            map_source.height = - (float) test_map_surface.texture.height;

            map_dest.x = camera->x;
            map_dest.y = camera->y;
            map_dest.width = (float) test_map_surface.texture.width * camera->zoom;
            map_dest.height = (float)test_map_surface.texture.height * camera->zoom;

            DrawTexturePro(test_map_surface.texture, map_source, map_dest, map_origin, 0.0f, WHITE);
        
            sys<SpriteRenderSystem>()->update(0);
        }

        void OnExit() override
        {
            Game::instance().unload_texture("tileset");
            Game::instance().unload_texture("player");

            //...

            UnloadRenderTexture(test_map_surface);
        }
    };
}