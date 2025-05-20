#pragma once

#include "../Tools/Externals.h"
#include "../ECS/SceneManager.h"
#include "../Map/RCamera.h"

namespace RetroCS
{
    namespace GameWindow
    {
        struct GameLogic : public SceneManager
        {
            Color background_color;
            MAP::RCamera* camera;

            GameLogic()
            {
                background_color = BLACK;
                camera = new MAP::RCamera();
            }

            virtual void enter() {}
            virtual void events(float delta) { scene()->events(delta); }
            virtual void update(float delta) { scene()->update(delta); }
            virtual void draw() { scene()->draw(); }
            virtual void exit() { scene()->exit(); }
        };
    }
}