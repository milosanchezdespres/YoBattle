#pragma once

#include "../RetroCS/RetroCS.h"

#include "Scenes/DebugMap.h"
using namespace YoBattleGame::ECS;

namespace YoBattleGame
{
    namespace GameWindow
    {
        struct YoBattle: public GameLogic
        {
            YoBattle() : GameLogic() { }

            void enter() override
            {
                GameLogic::enter();

                background_color = BLUE;

                go_to<DebugMap>();
            }

            void events() override
            {
                GameLogic::events();

                //...
            }
            
            void update(float delta) override
            {
                GameLogic::update(delta);

                //...
            }
            
            void draw() override
            {
                GameLogic::draw();
                
                //...
            }
            
            void exit() override
            {
                GameLogic::exit();
                
                //...
            }
        };
    }
}