#pragma once

#include "../../RetroCS/RetroCS.h"

#include "../Systems/SpriteRenderSystem.h"
#include "../Systems/StateMachineSystem.h"

#include "../Entities/Player.h"
#include "../Entities/NPC.h"
#include "../Entities/StartMenu.h"
//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct BaseMap : public Scene
        {
            bool display_map;
            metamap map;
            metatexture map_texture;

            Player* player;
            Vector2i spawn;

            bool camera_follow;
            string camera_target_alias;

            BaseMap() : Scene()
            {
                display_map = true;

                player = nullptr;
                spawn = {0, 0};

                camera_follow = true;
                camera_target_alias = "player";
            }

            void enter() override
            {
                Scene::enter();

                Game::instance().load_texture("tileset");
                //..

                Game::instance().load_texture("player");
                //..

                Game::instance().load_texture("uibox1");
                Game::instance().load_texture("uicursor1");
                //..

                HUB::init<bool>("input_required", false);
                //...

                Game::instance().register_key("up", KEY_W, GAMEPAD_BUTTON_LEFT_FACE_UP);
                Game::instance().register_key("down", KEY_S, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
                Game::instance().register_key("left", KEY_A, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
                Game::instance().register_key("right", KEY_D, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
                //...

                Game::instance().register_key("start", KEY_P, GAMEPAD_BUTTON_MIDDLE_RIGHT);
                Game::instance().register_key("confirm", KEY_M, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
                //...

                Game::instance().register_key("zoom-", KEY_KP_5);
                Game::instance().register_key("zoom+", KEY_KP_2);
                //...

                Game::instance().camera()->zoom = 7;

                attach<SpriteRenderSystem>();
                attach<ImageRenderSystem>();
                attach<StateMachineSystem>();
                attach<AnimationSystem>();
                attach<UIRenderSystem>();
                //..

                add<Player>("player");
                player = get<Player>("player");
                player->tp(spawn.i, spawn.j);

                add<StartMenu>("start_menu");
                get<StartMenu>("start_menu")->init();

                map = metamap();
                map_texture = metatexture();

                MAP::init(map, 128, 64);
                MAP::bind(map, map_texture);
                MAP::init(map_texture, "tileset");
            }

            void events(float delta) override
            {
                Scene::events(delta);

                if(Game::instance().is_pressed("start"))
                {
                    if(player->get<StateMachine>("states")->current() == "idle" && get<StartMenu>("start_menu")->is_disabled())
                    {
                        get<StartMenu>("start_menu")->enable();
                        HUB::set("input_required", true);
                    }
                    else
                    {
                        get<StartMenu>("start_menu")->disable();
                        HUB::set("input_required", false);
                    }
                }
            }

            void update(float delta) override
            {
                Scene::update(delta);

                if(camera_follow)
                {
                    Game::instance().camera()->follow(
                        get(camera_target_alias)->get<Sprite>("body")->x, 
                        get(camera_target_alias)->get<Sprite>("body")->y, 
                        MAP::tilesize(),
                        Game::instance().width,
                        Game::instance().height);
                }
            }
            
            void draw() override
            {
                MAP::render(map_texture);
                if(display_map) MAP::draw(map_texture);

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

                Game::instance().unregister_key("start");
                Game::instance().unregister_key("confirm");
                //...

                Game::instance().unregister_key("zoom-");
                Game::instance().unregister_key("zoom+");
                //...

                MAP::unbind(map);

                Scene::exit();
            }
        };
    }
}