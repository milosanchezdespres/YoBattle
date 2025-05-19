#pragma once

#include "../../../ECS/ECS.h"
#include "../Systems/SpriteRenderSystem.h"
#include "../Entities/Entity2D.h"

namespace YOBATTLE
{
    struct StartScreen : public Scene
    {
        StartScreen() : Scene() {}

        void OnEnter() override
        {
            Game::instance().load_texture("test");

            attach<SpriteRenderSystem>();

            add<Entity2D>("test");
            get("test")->get<Sprite>("body")->texture = "test";
            get("test")->get<Sprite>("body")->position.x = 130;
            get("test")->get<Sprite>("body")->position.y = 130;
            get("test")->get<Sprite>("body")->tile_index = 1;
            get("test")->get<Sprite>("body")->tile_size = 128;

            add<Entity2D>("test2");
            get("test2")->get<Sprite>("body")->texture = "test";
            get("test2")->get<Sprite>("body")->position.x = 243;
            get("test2")->get<Sprite>("body")->position.y = 243;
            get("test2")->get<Sprite>("body")->tile_index = 2;
            get("test2")->get<Sprite>("body")->tile_size = 128;

            add<Entity2D>("test3");
            get("test3")->get<Sprite>("body")->texture = "test";
            get("test3")->get<Sprite>("body")->position.x = 450;
            get("test3")->get<Sprite>("body")->position.y = 300;
            get("test3")->get<Sprite>("body")->width = 350;
            get("test3")->get<Sprite>("body")->height = 350;

            add<Entity2D>("test4");
            get("test4")->get<Sprite>("body")->texture = "test";
            get("test4")->get<Sprite>("body")->position.x = 780;
            get("test4")->get<Sprite>("body")->position.y = 178;

            sys<SpriteRenderSystem>()->upload(get("test")->get<Sprite>("body"));
            sys<SpriteRenderSystem>()->upload(get("test2")->get<Sprite>("body"));
            sys<SpriteRenderSystem>()->upload(get("test3")->get<Sprite>("body"));
            sys<SpriteRenderSystem>()->upload(get("test4")->get<Sprite>("body"));

            //...
        }
 
        void OnDraw() override
        {
            sys<SpriteRenderSystem>()->update(0);

            //...
        }

        void OnExit() override
        {
            Game::instance().unload_texture("test");

            //...
        }
    };
}