#pragma once

#include "../../../ECS/ECS.h"
#include "../Systems/SpriteRenderSystem.h"

namespace YOBATTLE
{
    struct StartScreen : public Scene
    {
        StartScreen() : Scene() {}

        void OnEnter() override
        {
            attach<SpriteRenderSystem>();

            add<Entity>("test");
            get("test")->add<Sprite>("debug_sprite");
            get("test")->get<Sprite>("debug_sprite")->position.x = 130;
            get("test")->get<Sprite>("debug_sprite")->position.y = 130;

            sys<SpriteRenderSystem>()->upload(get("test")->get<Sprite>("debug_sprite"));

            //...
        }

        void OnUpdate(float delta) override
        {
            //...
        }

        void OnDraw() override
        {
            sys<SpriteRenderSystem>()->update(0);

            //...
        }

        void OnExit() override
        {
            //...
        }
    };
}