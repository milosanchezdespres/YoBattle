#pragma once

#include "../Entities/Entity2D.h"
#include "../Components/State.h"
#include "../Components/Animator.h"

namespace YOBATTLE
{
    struct Character : public Entity2D
    {
        Character() : Entity2D() { }

        void OnInit() override
        {
            Entity2D::OnInit();

            add<State>("info");
            add<Animator>("anim");
            //...

            //...
        }

        void move(int i, int j, int TILE_SIZE, int camera_zoom)
        {
            get<Sprite>("body")->position.x = (float) (i * ((TILE_SIZE * 4) * camera_zoom));
            get<Sprite>("body")->position.y = (float) (j * ((TILE_SIZE* 4) * camera_zoom));
        }
    };
}