#pragma once

#include "../WINDOW/WINDOW.h"
using namespace RAYWIN;

#include "ECS/includes.h"

namespace YOBATTLE
{
    class YoBattle : public GameLogic
    {
        public:
            YoBattle() : GameLogic() {}

        protected:
            void OnStart() override
            {
                go_to<StartScreen>();
                
                //...
            }

            void OnUpdate() override
            {
                //...
            }
    };
}