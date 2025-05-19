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
                GameLogic::OnStart();

                go_to<StartScreen>();
            }
    };
}