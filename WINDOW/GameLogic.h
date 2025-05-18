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
            ~GameLogic() {}

            void start() { OnStart(); }
            void update() { OnUpdate(); }

        protected:
            virtual void OnStart() {}
            virtual void OnUpdate() {}
    };
}