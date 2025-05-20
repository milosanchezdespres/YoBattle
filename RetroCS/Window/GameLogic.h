#pragma once

#include "../Tools/Externals.h"
#include "../ECS/SceneManager.h"

namespace RetroCS
{
    namespace GameWindow
    {
        struct GameLogic : public SceneManager
        {
            Color background_color;

            GameLogic()
            {
                background_color = BLACK;
            }

            virtual void enter() {}
            virtual void events() { scene()->events(); }
            virtual void update(float delta) { scene()->update(delta); }
            virtual void draw() { scene()->draw(); }
            virtual void exit() { scene()->exit(); }
        };
    }
}