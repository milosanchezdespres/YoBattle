#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Components/Sprite.h"
#include "../Systems/SpriteRenderSystem.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Entity2D : public Entity
        {
            Entity2D () : Entity()
            {
                add<Sprite>("body");
                upload_to<SpriteRenderSystem, Sprite>(Game::instance().scene(), "body");

                get<Sprite>("body")->tile->size = MAP::tilesize();

                tp(0, 0);
            }

            virtual void tp(int i, int j)
            {
                get<Sprite>("body")->x = MAP::tile_to_screen(i, j).x;
                get<Sprite>("body")->y = MAP::tile_to_screen(i, j).y;
            }
            
            uint8_t tile_i() { return MAP::screen_to_tile(get<Sprite>("body")->x, get<Sprite>("body")->y).i; }
            uint8_t tile_j() { return MAP::screen_to_tile(get<Sprite>("body")->x, get<Sprite>("body")->y).j; }
        };
    }
}
