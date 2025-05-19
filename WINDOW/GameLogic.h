#pragma once

#include "../ECS/ECS.h"
using namespace ECS;

#include "raylib.h"

namespace RAYWIN
{
    class GameLogic : public SceneManager
    {
        public:
		    Color background = BLUE;

            GameLogic() : SceneManager() {}
            ~GameLogic() { scene()->Exit(); }

            void start() { OnStart(); }
            void update(float delta) override { SceneManager::update(delta); OnDraw(); }

        protected:
            virtual void OnStart() {}
            virtual void OnDraw() { scene()->Draw(); }
    };
}