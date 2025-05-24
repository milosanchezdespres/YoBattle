#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../entities/Entity2D.h"

namespace yokard
{
    namespace ecs
    {
        struct DebugScene : public Scene
        {
            DebugScene() : Scene() { }

            void _on_init() override
            {
                hub::data->background_color = BLUE;

                hub::data->load<texture>("player");
                //...

                const int spritesPerRow = 192;
                const int spriteSize = 16;
                const int verticalStep = 4;

                for (int i = 0; i < 50000; i++)
                {
                    string name = "test" + to_string(i);

                    add<Entity2D>(name);

                    auto sprite = get(name)->get<Sprite>();
                    sprite->texture = "player";

                    int col = i % spritesPerRow;
                    int row = i / spritesPerRow;

                    sprite->x = col * spriteSize;
                    sprite->y = row * verticalStep;

                    hub::screen->upload(sprite);
                }


                //...
            }

            void _on_enter() override
            {
                //...
            }

            void _on_exit() override
            {
                //...
            }

            void _on_destroy() override
            {
                //...
            }

            Scene* clone() const override { return new DebugScene(*this); }
        };
    }
}

//because this scene is entry_point :
using namespace yokard;
using namespace yokard::ecs;