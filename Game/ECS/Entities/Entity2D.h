#pragma once

#include "../../../ECS/ECS.h"
#include "../Components/Sprite.h"
#include "../Components/State.h"

namespace YOBATTLE
{
    struct Entity2D : public Entity
    {
        Entity2D() : Entity() { }

        void OnInit() override
        {
            add<Sprite>("body");

            //...
        }

        void move(int i, int j, int TILE_SIZE, int camera_zoom)
        {
            get<Sprite>("body")->position.x = (float) i * ((TILE_SIZE * camera_zoom) * 2);
            get<Sprite>("body")->position.y = (float) j * ((TILE_SIZE * camera_zoom) * 2);
        }
    };
}