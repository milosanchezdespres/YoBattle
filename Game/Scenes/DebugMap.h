#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Entities/UIBOX1.h"

#include "BaseMap.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct DebugMap : public BaseMap
        {
            DebugMap() : BaseMap() {}

            void enter() override
            {
                spawn = {5, 5};

                BaseMap::enter();

                add<NPC>("test_pnj");
                get<NPC>("test_pnj")->tp(10, 10);

                add<NPC>("test_pnj2");
                get<NPC>("test_pnj2")->tp(15, 15);

                add<NPC>("test_pnj3");
                get<NPC>("test_pnj3")->tp(0, 0);

                add<NPC>("test_pnj4");
                get<NPC>("test_pnj4")->tp(7, 3);
            }

            void events(float delta) override
            {
                BaseMap::events(delta);

                //FOR DEBUG PURPOSE
                
                if(Game::instance().is_down("zoom-") && Game::instance().camera()->zoom > 1)
                    { Game::instance().camera()->zoom_minus(Game::instance().width, Game::instance().height); }

                if(Game::instance().is_down("zoom+") && Game::instance().camera()->zoom < 10)
                    { Game::instance().camera()->zoom_plus(Game::instance().width, Game::instance().height); }
            }

            void update(float delta) override
            {
                BaseMap::update(delta);

                //...
            }
            
            void draw() override
            {
                //...

                BaseMap::draw();
            }
            
            void exit() override
            {
                //...

                BaseMap::exit();
            }
            
        };
    }
}