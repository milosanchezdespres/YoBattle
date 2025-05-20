#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Systems/SpriteRenderSystem.h"
#include "../Entities/Entity2D.h"
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
                Scene::enter();

                Game::instance().load_texture("tileset");
                Game::instance().load_texture("player");
                //..

                Game::instance().register_key("up", KEY_W, GAMEPAD_BUTTON_LEFT_FACE_UP);
                Game::instance().register_key("down", KEY_S, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
                Game::instance().register_key("left", KEY_A, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
                Game::instance().register_key("right", KEY_D, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
                //...

                Game::instance().register_key("zoom-", KEY_KP_5);
                Game::instance().register_key("zoom+", KEY_KP_2);
                //...

                Game::instance().camera()->zoom = 8;

                attach<SpriteRenderSystem>();
                //..

                add<Entity2D>("test_entity");
                component<Entity, Sprite>("test_entity", "body")->texture_alias = "player";
                get<Entity2D>("test_entity")->tp(2, 2);

                map = metamap();
                map_texture = metatexture();

                MAP::init(map, 100, 100);
                MAP::bind(map, map_texture);
                MAP::init(map_texture, "tileset");
            }

            void events(float delta) override
            {
                //FOR DEBUG PURPOSE

                Scene::events(delta);

                if(Game::instance().is_down("up")) { Game::instance().camera()->move_up(delta); }
                else if(Game::instance().is_down("down")) { Game::instance().camera()->move_down(delta); }
                else if(Game::instance().is_down("left")) { Game::instance().camera()->move_left(delta); }
                else if(Game::instance().is_down("right")) { Game::instance().camera()->move_right(delta); }

                if(Game::instance().is_down("zoom-") && Game::instance().camera()->zoom > 1) { Game::instance().camera()->zoom--; }
                if(Game::instance().is_down("zoom+") && Game::instance().camera()->zoom < 10) { Game::instance().camera()->zoom++; }
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
                //...

                Game::instance().unregister_key("up");
                Game::instance().unregister_key("down");
                Game::instance().unregister_key("left");
                Game::instance().unregister_key("right");
                //...

                MAP::unbind(map);

                Scene::exit();
            }
            
        };
    }
}