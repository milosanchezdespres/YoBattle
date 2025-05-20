#pragma once

#include "../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct DebugMap : public Scene
        {
            metamap map;
            metatexture map_texture;

            DebugMap() : Scene() {}

            void enter() override
            {
                Game::instance().load_texture("tileset");
                Game::instance().load_texture("player");

                map = metamap();
                map_texture = metatexture();

                MAP::init(map, 64, 64);
                MAP::bind(map, map_texture);
                MAP::init(map_texture, "tileset");
            }
            
            void draw() override
            {
                MAP::render(map_texture);
                MAP::draw(map_texture);

                Scene::draw();
            }
            
            void exit() override
            {
                Game::instance().unload_texture("tileset");
                Game::instance().unload_texture("player");

                MAP::unbind(map);
            }
            
        };
    }
}