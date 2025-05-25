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

                hub::camera->zoom = 4;

                const int spritesPerRow = 192;
                const int spriteSize = 16;
                const int verticalStep = 16;

                for (int i = 0; i < 250000; i++)
                {
                    string name = "test" + to_string(i);

                    add<Entity2D>(name);
                    get(name)->get<Sprite>()->tile_size = 16;
                    get(name)->get<Sprite>()->tile_index = 0;

                    auto sprite = get(name)->get<Sprite>();
                    sprite->texture = "player";

                    int col = i % spritesPerRow;
                    int row = i / spritesPerRow;

                    sprite->x = col * spriteSize;
                    sprite->y = row * verticalStep;

                    hub::screen->upload(hub::camera, sprite);
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