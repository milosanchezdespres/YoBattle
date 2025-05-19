#pragma once

#include <raylib.h>
#include "../../../ECS/ECS.h"
#include "../../../MAP/MAP.h"

#include "Sprite.h"
#include "../Entities/Character.h"

namespace YOBATTLE
{
    struct Controller : public Component
    {
        U8INT_MAP::Camera* camera;

        float move_speed;

        Controller() : Component()
        {
            camera = nullptr;
            move_speed = 0;
        }

        void update(Character* owner, float delta)
        {
            if(camera == nullptr || camera->mode != 1)
            {
                if (Game::instance().is_down("up"))
                {
                    owner->get<Sprite>("body")->position.y -= move_speed * delta;
                    owner->get<State>("info")->direction = 3;
                    owner->get<State>("info")->action = "walk";
                }
                else if (Game::instance().is_down("down"))
                {
                    owner->get<Sprite>("body")->position.y += move_speed * delta;
                    owner->get<State>("info")->direction = 0;
                    owner->get<State>("info")->action = "walk";
                }
                else if (Game::instance().is_down("left"))
                {
                    owner->get<Sprite>("body")->position.x -= move_speed * delta;
                    owner->get<State>("info")->direction = 6;
                    owner->get<State>("info")->action = "walk";
                }

                else if (Game::instance().is_down("right"))
                {
                    owner->get<Sprite>("body")->position.x += move_speed * delta;
                    owner->get<State>("info")->direction = 9;
                    owner->get<State>("info")->action = "walk";
                }
                else
                { owner->get<State>("info")->action = "idle"; }
            }
        }
    };
}