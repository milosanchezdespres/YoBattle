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
        mapsurface test_map_surface;

        StartScreen() : Scene() {}

        void OnEnter() override
        {
            Game::instance().load_texture("tileset");
            Game::instance().load_texture("player");

            test_map_surface = mapsurface();
            test_map_surface.init(50, 50);

            attach<SpriteRenderSystem>();
            sys<SpriteRenderSystem>()->camera = test_map_surface.camera;
            sys<SpriteRenderSystem>()->camera->mode = 1;
            sys<SpriteRenderSystem>()->camera->zoom = 5;

            add<Character>("player");
            get("player")->get<Sprite>("body")->texture = "player";
            get("player")->get<Sprite>("body")->position.x = 130;
            get("player")->get<Sprite>("body")->position.y = 130;
            get("player")->get<Sprite>("body")->tile_index = 1;
            get("player")->get<Sprite>("body")->tile_size = 16;

            sys<SpriteRenderSystem>()->upload(get("player")->get<Sprite>("body"));
        }
 
        void OnDraw() override
        {
            test_map_surface.refresh();

            test_map_surface.draw();
        
            sys<SpriteRenderSystem>()->update(GetFrameTime());
        }

        void OnExit() override
        {
            Game::instance().unload_texture("tileset");
            Game::instance().unload_texture("player");

            test_map_surface.clear();
        }
    };
}