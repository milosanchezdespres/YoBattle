#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Systems/SpriteRenderSystem.h"
//...

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

                attach<SpriteRenderSystem>();
                //..

                add<Entity>("test_entity");
                add_component<Sprite>("test_entity", "body");
                component<Entity, Sprite>("test_entity", "body")->texture_alias = "player";
                component<Entity, Sprite>("test_entity", "body")->tile->size = 16;
                component<Entity, Sprite>("test_entity", "body")->x = 150;
                component<Entity, Sprite>("test_entity", "body")->y = 150;

                upload_to<SpriteRenderSystem, Sprite>(get("test_entity"), "body");

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