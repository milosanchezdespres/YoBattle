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

            sys<SpriteRenderSystem>()->upload(get("test")->get<Sprite>("body"));

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