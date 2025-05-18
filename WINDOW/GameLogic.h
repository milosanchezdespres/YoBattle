#pragma once

#include "raylib.h"

namespace RAYWIN
{
    class GameLogic
    {
        public:
		    Color background = BLUE;

            GameLogic() {}
            ~GameLogic() {}

            void start() { OnStart(); }
            void update() { OnUpdate(); }

        protected:
            virtual void OnStart() {}
            virtual void OnUpdate() {}
    };
}