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
            sys<SpriteRenderSystem>()->camera->mode = 2;
            sys<SpriteRenderSystem>()->camera->zoom = 5;

            add<Character>("player");
            get("player")->get<Sprite>("body")->texture = "player";
            get("player")->get<Sprite>("body")->tile_index = 1;
            get("player")->get<Sprite>("body")->tile_size = 16;

            sys<SpriteRenderSystem>()->upload(get("player")->get<Sprite>("body"));

            Game::instance().register_key("up", KEY_W, GAMEPAD_BUTTON_LEFT_FACE_UP);
            Game::instance().register_key("down", KEY_S, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
            Game::instance().register_key("left", KEY_A, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
            Game::instance().register_key("right", KEY_D, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
        }

        void OnUpdate(float delta) override
        {
            sys<SpriteRenderSystem>()->camera->update(delta);

            sys<SpriteRenderSystem>()->camera->update_follow(
                get("player")->get<Sprite>("body")->position, 
                get("player")->get<Sprite>("body")->tile_size, 
                get("player")->get<Sprite>("body")->tile_size);
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