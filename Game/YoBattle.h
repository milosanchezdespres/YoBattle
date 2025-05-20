#pragma once

#include "../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace GameWindow
    {
        struct YoBattle: public GameLogic
        {
            metamap test_map;
            metatexture test_texture;

            YoBattle() : GameLogic() { }

            void enter() override
            {
                background_color = BLUE;

                Game::instance().load_texture("tileset");

                //...

                test_map = metamap();
                test_texture = metatexture();

                MAP::init(test_map, 64, 64);
                MAP::bind(test_map, test_texture);
                MAP::init(test_texture, "tileset");
            }

            void events() override
            {
                //...
            }
            
            void update(float delta) override
            {
                //...
            }
            
            void draw() override
            {
                //...

                MAP::render(test_texture);
                MAP::draw(test_texture);
            }
            
            void exit() override
            {
                //...

                MAP::unbind(test_map);
            }
        };
    }
}